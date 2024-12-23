from z3 import *

def main():
    # Variables
    p_var = Int("p_var")
    q_var = Int("q_var")
    e_exponent = Int("e_exponent")
    d_exponent = Int("d_exponent")

    # combininations of existing vars
    keys_product = p_var * q_var
    
    product_off1 = ( p_var -1) *(q_var-1)

    # Constraints
    condition1 = e_exponent < product_off1
    condition2 = d_exponent < product_off1
    condition3 = (d_exponent * e_exponent) % product_off1 != 1

    # Negative constraint: NOT all conditions hold simultaneously
    negative_constraint = Not(And(condition1, condition2, condition3))

    condition4= keys_product>0xFF

    s = Solver()
    # s.add(negative_constraint)
    s.add(e_exponent > product_off1)
    s.add(condition4)

    if s.check() == sat:
        model = s.model()
        print(model)
    else:
        print("No more solutions found.")

if __name__ == "__main__":
    main()
