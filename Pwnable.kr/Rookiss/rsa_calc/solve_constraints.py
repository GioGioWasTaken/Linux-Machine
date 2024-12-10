from z3 import *

def main():
    # Variables
    public_key = Int("public_key")
    private_key = Int("private_key")
    e_exponent = Int("e_exponent")
    d_exponent = Int("d_exponent")

    # combininations of existing vars
    keys_product = public_key * private_key
    
    product_off1 = ( public_key -1) *(private_key-1)

    # Constraints
    condition1 = e_exponent < product_off1
    condition2 = d_exponent < product_off1
    condition3 = (d_exponent * e_exponent) % product_off1 != 1

    # Negative constraint: NOT all conditions hold simultaneously
    negative_constraint = Not(And(condition1, condition2, condition3))

    condition4= keys_product>0xFF

    s = Solver()
    s.add(negative_constraint)
    s.add(condition4)

    block_solution = [private_key != -128, d_exponent != 1, e_exponent != 388, public_key != -2,]

    for block in block_solution:
        s.add(block)

    if s.check() == sat:
        model = s.model()
        print(model)
    else:
        print("No more solutions found.")

if __name__ == "__main__":
    main()
