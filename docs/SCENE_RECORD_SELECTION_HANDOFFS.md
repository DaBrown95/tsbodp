# Record-selection handoffs, panel and shutdown

Milestone 124 contains four ordinary matching C bodies, totaling 804 bytes.
Fresh public normal and strict positives reproduce the complete original spans;
the matching controls reject in both profiles. The importer and full-ROM gates
pass separately. The existing six-function record-selection batch is documented
[separately](RECORD_SELECTION_RECONSTRUCTION.md).

| ROM offset | Body | Instruction bytes | Literal bytes | Zero alignment | Full span |
| --- | --- | ---: | ---: | ---: | ---: |
| `0x253B0` | Set phase | 218 | 24 | 2 | 244 |
| `0x254A4` | Set slot phase | 184 | 20 | 0 | 204 |
| `0x25570` | Draw panel | 268 | 36 | 4 | 308 |
| `0x2579C` | Shutdown | 40 | 8 | 0 | 48 |
| **Total** | | **710** | **88** | **6** | **804** |

The bounded original-image walks and actual matching assembly corroborate this
breakdown. All six alignment bytes are retained zeros associated with explicit
assembler alignment. They are neither removed nor counted as instructions.
These four functions add no low-level glue.

## Canonical owners

The sole 312-byte `FrameObject` retains the same layout and callback fields.
Its 60-byte `motion_storage` union at offset `0x4C` preserves the old character
representation and adds the observed unsigned-short timer at `0x5E`. Three
existing bodies use only a mechanical change to the byte-member path. The
existing palette-scene point tag and array declaration move to one guarded
header without creating another point owner.

The sole 108-byte `BackgroundState` retains a four-byte byte/pointer union at
offset 4. Its pointer member is `const unsigned short *`, matching the loader
interface. The enclosing 440-byte display owner places background one's map
pointer at offset 120. This view requires an initialized map pointer in this
scene; it does not assert that every background state holds a map or that a
separately named stored-map tag is compatible.

The sole 40-byte `SaveStreamRecord` retains an eight-byte clock union at offset
4, with both the original six serialized bytes plus two reserved bytes and the
canonical `DisplayTimeRecord` member. The target clock is eight bytes aligned
to four. The existing loader changes only its field path and still loads six
bytes. No reserved-byte initialization or extra clock read is invented. The
selected GNU compiler and target representation qualify this union view.

Target checks preserve sizes, alignment, field offsets, extents and callback
interfaces. Same-size wrong map-pointee, foreign clock-tag, signed timer and
wrong callback-object declarations are separately rejected. Byte equality alone
is not used to infer tag or pointee compatibility.

## Behaviour and source domains

The first handoff initializes its actual index before the point-table producer,
captures departure X before loading Y, and retains the timer reread after the
position setter. The second supplies literal duration 16 and preserves its
distinct background and object-flag effects. Both contain one slot-zero
iteration; a null slot zero skips the object branch. The second separately
requires live nonnull objects in slots 4 and 5. Direction is an unsigned byte
and the return phase is a full unsigned word.

Signed-short point coordinates are multiplied by 65,536 rather than shifted as
negative signed values. Each product is representable, but later position
addition, subtraction and movement-provider arithmetic still require their
own representable-input domains. Live object/resource ownership and callback
contracts are not inferred from native equality.

The panel selects the current record, distinguishes occupied and enabled flags,
and passes the actual map pointer to the original map service. Its palette
comes from a conditional expression after the enabled-byte read. Record selection
is freshly read where the original does so; the captured record and subsequent
selector reads are not silently synchronized across calls. Valid calls require
selectors 0–3, a live sixteen-byte scene state, initialized record/clock fields,
a terminated record name when used, and output fitting the 32-byte formatting
buffer under the chosen text/format contracts.

Shutdown invokes transition kind 12, clears indexed audio, releases the object
list, resets display state and slots, then frees the current scene allocation.
The original second-handler table slot at `0x0806A248` contains Thumb target
`0x08039041`; that callback has no accepted C owner in this batch. The original
map service at `0x0800CEFC` and text renderer at `0x0801AA78` also remain explicit
unconverted boundaries. The phase-seven initializer at `0x08024E18` is still
unconverted. Their bodies are not transcribed into claimed C or a source model.

The 32 public native roles cover the new four and the four existing field-path
repairs, with full snapshots, dependencies, commands and ELF/source ownership.
The old shutdown proof used an earlier header context; the fresh public roles
now use the complete merged owners. These are static and compiler results.
The historical finite qualification covers only the 708-byte update with its
declared service abstractions; it does not become a new four-body finite proof.
Hardware, complete allocator/resource behaviour and gameplay remain untested.

Milestone 125 subsequently reconstructs the kind-12 second handler and its paired
first handler as the [mosaic transitions](TRANSITION_MOSAIC_REFRESH.md). Each has
its own matching source/control roles and separately scoped finite execution
evidence. This closes the shutdown transition boundary described above; the map
service, text renderer and phase-seven initializer remain unconverted. The
first-handler kind-12 connection is still static table evidence without an
observed executed caller.
