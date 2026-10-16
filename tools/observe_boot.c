/* Bounded GBA boot observation with mGBA 0.10.5.
 * Entry labels describe probe addresses, not established execution ownership.
 * See docs/RUNTIME_OBSERVATIONS.md for build steps and observation limits. */
#include <mgba/flags.h>
#include <mgba/core/core.h>
#include <mgba/core/timing.h>
#include <mgba/core/log.h>
#include <mgba/debugger/debugger.h>
#include <mgba/internal/arm/arm.h>
#include <mgba/internal/gba/gba.h>
#include <mgba-util/vfs.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

struct Probe { uint32_t address; const char *name; ssize_t id; uint64_t hits; };
static struct Probe entries[] = {
 {0x080000c0,"reset"}, {0x08025c0c,"game_entry"},
 {0x0800109c,"frame_install_runtime"}, {0x08016a48,"resource_install"},
 {0x080023e8,"frame_render_object"}, {0x08003248,"frame_finalize_object"},
 {0x08039e78,"map_install"}, {0x08047724,"tile_allocator_install"},
 {0x08041258,"audio_game_initialize"}, {0x08049968,"audio_master_volume"},
 {0x080499b0,"audio_master_volume_nop"},
 {0x03000004,"audio_timer_irq"}, {0x03000bf0,"audio_shift_patcher"},
 {0x0300004c,"audio_irq_reprogram_or_return"},
 {0x03000604,"audio_mix_left"}, {0x03000ab4,"audio_mix_bias"},
 {0x03000b38,"audio_mix_convert"},
 {0x03000b70,"audio_convert_pair0_a"}, {0x03000b74,"audio_convert_pair0_b"},
 {0x03000b8c,"audio_convert_pair1_a"}, {0x03000b90,"audio_convert_pair1_b"},
 {0x03000bb0,"audio_convert_pair2_a"}, {0x03000bb4,"audio_convert_pair2_b"},
 {0x03000bcc,"audio_convert_pair3_a"}, {0x03000bd0,"audio_convert_pair3_b"},
 {0x03002900,"frame_sort"}, {0x03002a20,"frame_collisions"},
 {0x030036d0,"tile_decoder"}, {0x03003370,"background_decoder"},
 {0x03007160,"map_draw"}, {0x03005e60,"map_transfer"},
 {0x03007390,"tile_allocator"},
 {0x08046eb0,"display_pending_initialize"},
 {0x08046e50,"display_pending_vcount"},
 {0x08046e6e,"display_pending_indirect_call"},
 {0x08047080,"display_pending_default_callback"}
};
static struct Probe writes[] = {
 {0x0300004c,"irq_reprogram_word"},
 {0x03000b70,"convert_pair0_a"}, {0x03000b74,"convert_pair0_b"},
 {0x03000b8c,"convert_pair1_a"}, {0x03000b90,"convert_pair1_b"},
 {0x03000bb0,"convert_pair2_a"}, {0x03000bb4,"convert_pair2_b"},
 {0x03000bcc,"convert_pair3_a"}, {0x03000bd0,"convert_pair3_b"},
 {0x03003360,"tile_decoder_callback"}, {0x030036c0,"background_decoder_callback"},
 {0x03001fc8,"map_draw_callback"}, {0x03001fcc,"map_transfer_callback"},
 {0x03007ffc,"bios_irq_vector"}
 ,{0x02000e38,"clip_negative_endpoint"}, {0x22000e38,"bad_literal_destination"},
 {0x03002260,"display_staged_first_callback"},
 {0x03002310,"display_queued_first_callback"}
};
static uint64_t steps;
static uint64_t event_count;
static int invalid_event;
static struct { uint32_t address; uint64_t event; } pending[64];
static size_t pending_count;
static uint64_t log_counts[7];

static bool bounded_number(const char *text,uint64_t maximum,uint64_t *out) {
 char *end;
 errno=0;
 if(!*text || *text=='-') return false;
 unsigned long long number=strtoull(text,&end,0);
 if(errno || *end || number>maximum) return false;
 *out=number;
 return true;
}

static void logger(struct mLogger *unused,int category,enum mLogLevel level,const char *fmt,va_list args) {
 (void)unused;
 for(unsigned i=0;i<7;++i) if(level&(1u<<i)) ++log_counts[i];
 if(level&(mLOG_FATAL|mLOG_ERROR|mLOG_WARN)) {
  fprintf(stderr,"%s: ",mLogCategoryName(category)); vfprintf(stderr,fmt,args); fputc('\n',stderr);
 }
}

static void regs(struct mCore *core) {
 struct ARMCore *cpu=core->cpu;
 printf(",\"frame\":%u,\"ticks\":%"PRIu64",\"steps\":%"PRIu64
        ",\"raw_pc\":%u,\"cpsr\":%u,\"lr\":%u,\"sp\":%u,\"r\":[",
        core->frameCounter(core),mTimingGlobalTime(core->timing),steps,
        (uint32_t)cpu->gprs[15],cpu->cpsr.packed,(uint32_t)cpu->gprs[14],(uint32_t)cpu->gprs[13]);
 for(int i=0;i<13;++i) printf("%s%u",i?",":"",(uint32_t)cpu->gprs[i]);
 printf("]");
}

static void entered(struct mDebugger *debugger, enum mDebuggerEntryReason reason,
                    struct mDebuggerEntryInfo *info) {
 struct Probe *probe=NULL;
 if(reason==DEBUGGER_ENTER_BREAKPOINT) {
  for(size_t i=0;i<sizeof(entries)/sizeof(*entries);++i)
   if(entries[i].id==info->pointId) probe=&entries[i];
 } else if(reason==DEBUGGER_ENTER_WATCHPOINT) {
  for(size_t i=0;i<sizeof(writes)/sizeof(*writes);++i)
   if(writes[i].id==info->pointId) probe=&writes[i];
 }
 if(!probe) {
  printf("{\"event\":\"unexpected_debugger_entry\",\"reason\":%d}\n",reason);
  invalid_event=1;
 } else if(++probe->hits<=8) {
  printf("{\"event\":\"%s\",\"name\":\"%s\",\"address\":%u,\"hit\":%"PRIu64,
    reason==DEBUGGER_ENTER_BREAKPOINT?"entry":"pre_write",probe->name,info->address,probe->hits);
  printf(",\"event_index\":%"PRIu64,event_count);
  regs(debugger->core);
  if(reason==DEBUGGER_ENTER_WATCHPOINT)
   printf(",\"shim_old_value\":%u,\"shim_proposed_value_untrusted\":%u,\"access_type\":%d,\"performing_dma\":%s",
    info->type.wp.oldValue,info->type.wp.newValue,info->type.wp.accessType,
    ((struct GBA*)debugger->core->board)->performingDMA?"true":"false");
  if(reason==DEBUGGER_ENTER_WATCHPOINT && pending_count<64) {
   pending[pending_count].address=info->address;
   pending[pending_count++].event=event_count;
  }
  if(reason==DEBUGGER_ENTER_BREAKPOINT)
   printf(",\"instruction_word\":%u",debugger->core->busRead32(debugger->core,probe->address));
  if(reason==DEBUGGER_ENTER_BREAKPOINT &&
     (probe->address==0x03000bf0 || probe->address==0x03000b38)) {
   printf(",\"patch_words_before\":[");
   for(size_t i=1;i<9;++i) printf("%s%u",i>1?",":"",debugger->core->busRead32(debugger->core,writes[i].address));
   printf("]");
  }
  printf("}\n");
  ++event_count;
 }
 debugger->state=DEBUGGER_RUNNING;
}

int main(int argc,char **argv) {
 if(argc!=5) { fprintf(stderr,"usage: trace ROM frames max_steps watch_shift\n"); return 2; }
 uint64_t frame_value,max_steps,shift_value;
 if(!bounded_number(argv[2],3600,&frame_value) || !frame_value ||
    !bounded_number(argv[3],100000000,&max_steps) || !max_steps ||
    !bounded_number(argv[4],0x10000000,&shift_value) ||
    (shift_value!=0 && shift_value!=0x10000000)) {
  fprintf(stderr,"invalid bounded observation arguments\n"); return 2;
 }
 uint32_t frames=(uint32_t)frame_value;
 uint32_t watch_shift=(uint32_t)shift_value;
 struct mLogger log={.log=logger};
 mLogSetDefaultLogger(&log);
 struct mCore *core=mCoreCreate(mPLATFORM_GBA);
 if(!core || !core->init(core)) return 3;
 mCoreInitConfig(core,NULL);
 core->opts.useBios=false;
 core->opts.skipBios=true;
 core->opts.audioBuffers=1024;
 core->setAudioBufferSize(core,1024);
 core->rtc.override=RTC_FIXED;
 core->rtc.value=0;
 struct VFile *rom=VFileOpen(argv[1],O_RDONLY);
 if(!rom || !core->loadROM(core,rom)) return 4;
 struct mDebugger debugger={0};
 debugger.type=DEBUGGER_CUSTOM;
 debugger.entered=entered;
 mDebuggerAttach(&debugger,core);
 core->reset(core);
 for(size_t i=0;i<sizeof(entries)/sizeof(*entries);++i) {
  struct mBreakpoint p={.address=entries[i].address,.segment=-1,.type=BREAKPOINT_HARDWARE};
  entries[i].id=debugger.platform->setBreakpoint(debugger.platform,&p);
  if(entries[i].id<0) return 5;
 }
 for(size_t i=0;i<sizeof(writes)/sizeof(*writes);++i) {
  struct mWatchpoint p={.address=writes[i].address+watch_shift,.segment=-1,.type=WATCHPOINT_WRITE};
  writes[i].id=debugger.platform->setWatchpoint(debugger.platform,&p);
  if(writes[i].id<0) return 6;
 }
 printf("{\"event\":\"start\",\"bios\":\"mGBA_HLE_skip\",\"rtc\":0,\"keys\":0,\"frame_limit\":%u,\"step_limit\":%"PRIu64",\"watch_shift\":%u",frames,max_steps,watch_shift);
 regs(core); printf("}\n");
 debugger.platform->checkBreakpoints(debugger.platform);
 while(core->frameCounter(core)<frames && steps<max_steps && !invalid_event) {
  ++steps;
  mDebuggerRun(&debugger);
  for(size_t i=0;i<pending_count;++i)
   printf("{\"event\":\"after_step_readback\",\"pre_write_event\":%"PRIu64",\"address\":%u,\"word\":%u,\"steps\":%"PRIu64"}\n",
    pending[i].event,pending[i].address,core->busRead32(core,pending[i].address),steps);
  pending_count=0;
 }
 printf("{\"event\":\"end\",\"reason\":\"%s\",\"recorded_events\":%"PRIu64,
  invalid_event?"unexpected_debugger_entry":core->frameCounter(core)>=frames?"frame_limit":"step_limit",event_count);
 regs(core);
 printf(",\"entries\":[");
 for(size_t i=0;i<sizeof(entries)/sizeof(*entries);++i)
  printf("%s{\"name\":\"%s\",\"address\":%u,\"hits\":%"PRIu64"}",i?",":"",entries[i].name,entries[i].address,entries[i].hits);
 printf("],\"writes\":[");
 for(size_t i=0;i<sizeof(writes)/sizeof(*writes);++i) {
  printf("%s{\"name\":\"%s\",\"watched_address\":%u,\"hits\":%"PRIu64,i?",":"",writes[i].name,writes[i].address+watch_shift,writes[i].hits);
  if(!watch_shift && writes[i].address<0x10000000)
   printf(",\"final_value\":%u",core->busRead32(core,writes[i].address));
  printf("}");
 }
 printf("],\"log_counts_fatal_error_warn_info_debug_stub_gameerror\":[");
 for(int i=0;i<7;++i) printf("%s%"PRIu64,i?",":"",log_counts[i]);
 printf("]}\n");
 core->detachDebugger(core);
 mCoreConfigDeinit(&core->config);
 core->deinit(core);
 return invalid_event?7:0;
}
