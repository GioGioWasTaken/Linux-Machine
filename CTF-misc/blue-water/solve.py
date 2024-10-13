import angr
import claripy

def solve_ctf():
    input_file_path = './flute'
    known_string = 'bwctf{'
    max_flag_suffix_length = 14  # Maximum length for the suffix after 'bwctf{'
    FIND_ADDR = 0x4BCAD0

    PANIC_FUNCS = [0x46C660, 0x4309A]
    XOR_CHAIN = 0x4A8AB2
    JUICE_MACHINE_BROKE = 0x4BCB15

    AVOID_ADDR = [JUICE_MACHINE_BROKE, XOR_CHAIN]
    AVOID_ADDR += PANIC_FUNCS

    # Load the binary
    proj = angr.Project(input_file_path, auto_load_libs=False)

    # Iterate through possible lengths
    for suffix_length in range(1, max_flag_suffix_length + 1):
        print("Checking for input length: ", suffix_length)
        flag_length = len(known_string) + suffix_length
        flag = claripy.BVS('flag', 8 * flag_length)

        # Lazy solves to take less CPU power
        extras = {angr.options.LAZY_SOLVES}

        # Create initial state
        state = proj.factory.entry_state(args=[input_file_path, flag], add_options=extras)

        # Add constraints for known part of the flag
        for i, c in enumerate(known_string):
            state.solver.add(flag.get_byte(i) == ord(c))

        # Add constraints for printable characters in the unknown part of the flag
        for i in range(len(known_string), flag_length - 1):
            state.solver.add(flag.get_byte(i) >= ord('!'))
            state.solver.add(flag.get_byte(i) <= ord('~'))

        # Add constraint for the closing brace
        state.solver.add(flag.get_byte(flag_length - 1) == ord('}'))

        # Create simulation manager and explore
        sim_manager = proj.factory.simulation_manager(state)
        sim_manager.explore(find=FIND_ADDR, avoid=AVOID_ADDR)

        # optimization
        sim_manager.use_technique(angr.exploration_techniques.Veritesting())

        if len(sim_manager.found) > 0:
            found_state = sim_manager.found[0]
            solution = found_state.solver.eval(flag, cast_to=bytes)
            return solution.decode('utf-8')

    return "No solution found"

if __name__ == "__main__":
    print(solve_ctf())
