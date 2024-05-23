import sys
if __name__ == "__main__":
    # Check command line arguments
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <Score amount to pass>")
        print("")
        sys.exit(1)

    array = [1,3,5,7,10,1,4,2,1,1,6,1,2,1,9,8,10,6,10,3,7,150,200,50,100,33,30,20,75,35,200,120,25,50,200,200,80,50,400,444,333,550,111,150,100,111,300,150,100,300,300,400,200,200,500,600,666,700,222,500,99,99,500,250,500,600,200]
    input = sys.argv[1]

    sum = 0
    i = 0
    while(sum < int(input)):
       sum+=array[i] 
       i+=1
    if(i >=21):
        print("[Toddler's Bottle] ✅︎ required")
    else:
        print(f"[Toddler's Bottle] [{i}/21] required")

    if(i >=38):
        print("[Rookiss] ✅︎ required")
    else:
        result = i - 21 if i - 21 > 0 else 0
        print(f"[Rookiss] [{result}/21] required")

    if(i >=54):
        print("[Grotesque] ✅︎ required" )
    else:
        result = i - 38 if i - 38 > 0 else 0
        print(f"[Grotesque] [{result}/21] required")

    if(i >=67):
        print("[Hacker's Secret] ✅︎ required")
    else:
        result = i - 54 if i - 54 > 0 else 0
        print(f"[Hacker's Secret] [{result}/21] required")
