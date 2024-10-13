import angr
import claripy

input_file_path = './flute'
flag_length = 100
known_string = 'bwctf{'
FIND_ADDR = 0x4BCAD0

PANIC_FUNCS = [0x46C660, 0x4309A]
XOR_CHAIN = 0x4A8AB2
JUICE_MACHINE_BROKE = 0x4BCB15

AVOID_ADDR = [JUICE_MACHINE_BROKE, XOR_CHAIN]
AVOID_ADDR += PANIC_FUNCS

proj = angr.Project(input_file_path, main_opts={'base_addr': 0x00})

# Known prefix characters
known_chars = [claripy.BVV((known_string[i]), 8) for i in range(len(known_string))]

# Lazy solves to take less CPU power
extras = {angr.options.LAZY_SOLVES}

# Loop over possible suffix lengths
for suffix_length in range(flag_length - len(known_string) + 1):  # 0 to 93
    print("Current suffix length : ", suffix_length)

    flag_chars = [claripy.BVS(f"flag_{i}", 8) for i in range(suffix_length)]
    # Construct the full flag including the known prefix, current suffix, and closing brace
    flag = claripy.Concat(*known_chars + flag_chars + [claripy.BVV(ord('}'), 8)])

    print(flag)

    # Create initial state for each length
    state = proj.factory.entry_state(args=[input_file_path, flag], add_options=extras)

    sim_manager = proj.factory.simulation_manager(state)
    sim_manager.explore(find=FIND_ADDR, avoid=AVOID_ADDR)

    if len(sim_manager.found) > 0:
        print(f"Suffix length {suffix_length}: {sim_manager.found[0].solver.eval(flag, cast_to=bytes)}")
