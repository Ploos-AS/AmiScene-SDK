# Target definitions

## a500-ocs — primary baseline
- Motorola 68000
- OCS
- PAL first
- A500-class timing assumptions
- 1 MiB total RAM where practical
- no accelerator, FPU or RTG assumptions

## ecs
ECS capabilities must be requested explicitly. OCS code must not silently gain ECS dependencies.

## a1200-aga
Planned explicit target: A1200-class, 68020 baseline, AGA. AGA must not become an implicit default.

## Qualification
Host tests, supported emulators and physical hardware are complementary qualification layers.
