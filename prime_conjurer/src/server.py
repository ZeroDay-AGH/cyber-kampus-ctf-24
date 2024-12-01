from math import prod
import random

from secret import FLAG

motd = """
                                 In a world of numbers, rare and bright,
                                 Primes are the stars that light the night.
               (       "     )   Unyielding, unique, they dance and gleam,
                ( _  *           A mathematician's secret, a wizard's dream.
                   * (     /      \    ___
                      "     "        _/ /
                     (   *  )    ___/   |
                       )   "     _ o)'-./__
                      *  _ )    (_, . $$$
                      (  )   __ __ 7_ $$$$
                       ( :  { _)  '---  $\\
                  ______'___//__\   ____, \\
                   )           ( \_/ _____\_
                 .'             \   \------''.
                 |='           '=|  |         )
                 |               |  |  .    _/
                  \    (. ) ,   /  /__I_____\\
              snd  '._/_)_(\__.'   (__,(__,_]
                  @---()_.'---@
"""

def is_prime(n):
    if n == 2: return True
    if n%2 == 0: return False
    r,d = 0,n-1
    while d%2 == 0: r += 1; d //= 2
    for k in range(1):
        a = random.randint(2,n-2)
        x = pow(a,d,n)
        if x == 1 or x == n-1: continue
        for i in range(r-1):
            x = pow(x,2,n)
            if x == n-1: continue
        else: return False
    return True

def main():
    print(motd)
    numbers = []
    print("The whispers of the ancients echo through the void: only those who understand the prime magic may proceed. Are you ready to cast your spell of discovery?")
    while len(numbers) < 3:
        try:
            print("Summon the ancient number, seeker of mysteries: ")
            num = int(input())
        except ValueError:
            print("The magic stirs and warns you: the input is not true. Enter a valid number, or be lost in the void of confusion.")
            continue

        if num in numbers:
            print('The echoes of the past resound: you have already summoned this number.')
            continue

        if not is_prime(num):
            print(f"The ancient runes whisper their secrets, and the echoes reveal the truth: this number is not prime.")
            continue
        
        print("Speak the names of the elements that bind this number, separated by space: ")
        number_list = input()
        try:
            factors = list(map(int,number_list.strip().split()))
        except ValueError:
            print("The magic stirs and warns you: the input is not true. Enter a valid number, or be lost in the void of confusion.")
            continue

        if 1 in factors or len(factors) < 2:
            print("Are you trying to fool me?")
            continue

        if prod(factors) != num:
            print("The whispers of the numbers reveal the truth: these are not the factors of the number you provided.")
            continue
        
        numbers.append(num)
    
    print(f"The spell is complete, and the forces align. Success! Your reward appears, a token of your triumph and mastery: {FLAG}")


        

if __name__ == "__main__":
    main()
