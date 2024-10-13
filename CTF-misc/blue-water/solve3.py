import angr
import claripy

FIND_ADDR = 0x4BCAD0

PANIC_FUNCS = [0x46C660, 0x4309A]
XOR_CHAIN = 0x4A8AB2
JUICE_MACHINE_BROKE = 0x4BCB15
AVOID_ADDR = [JUICE_MACHINE_BROKE, XOR_CHAIN]
AVOID_ADDR += PANIC_FUNCS


def solveCTF():

    project=  angr.Project("./flute")

    # Define the size of the input
    input_size = 100 * 8  # 100 bytes
    input_val = claripy.BVS("input", input_size)


    start = 0x4A8505

    state = project.factory.blank_state(addr=start)
    state.options |= {angr.sim_options.LAZY_SOLVES}

    for byte in input_val.chop(8):
        state.add_constraints(byte >= 0x0a)
        state.add_constraints(byte < 0x7f)

    # Constraints for the symbolic input
    # Ensuring the prefix is "bwctf{"
    prefix = b'bwctf{'
    for i in range(len(prefix)):
        byte = input_val.get_byte(i)
        state.add_constraints(byte == prefix[i])

    # Allowing characters in the range [0x0A, 0x7F]
    for byte in input_val.chop(8):
        state.add_constraints(byte >= 0x0a)
        state.add_constraints(byte < 0x7f)

    # Ensure that the input does not exceed 100 characters (including closing brace)

    closing_brace = input_val.get_byte(99)  # Assuming the last character can be '}'
    state.add_constraints(closing_brace == ord('}'))


    state.memory.store(state.regs.sp-0xb0,input_val)
    print("set input")

    simulation = project.factory.simgr(state)

    simulation.explore(find=FIND_ADDR, avoid=AVOID_ADDR)

    if (simulation.found):
        s = simulation.found[0]
        flag = s.solver.eval(input_val, cast_to=bytes)
        print(flag)

if __name__ =="__main__":
    solveCTF()
