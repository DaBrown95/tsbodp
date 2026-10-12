/* Partial link state view supported by the connected shutdown/recording path. */
struct LinkEndpointState {
 int identifier;
 unsigned char active, slot;
};
extern struct LinkEndpointState g_link_endpoint;
extern volatile unsigned int g_link_flags;
extern unsigned int g_link_recording;
extern unsigned char link_transfer_finished(void);
