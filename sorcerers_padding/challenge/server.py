import hashlib
from secret import SECRET, FLAG

motd = """
                             /\\
                            /  \\
                           |    |
                         --:'''':--
                           :'_' :
                           _:"":\___
            ' '      ____.' :::     '._
           . *=====<<=)           \    :
            .  '      '-'-'\_      /'._.'
                             \====:_ ""
                            .'     \\
                           :       :
                          /   :    \\
                         :   .      '.
         ,. _        snd :  : :      :
      '-'    ).          :__:-:__.;--'
    (        '  )        '-'   '-'
 ( -   .00.   - _
(    .'  _ )     )
'-  ()_.\,\,   -
"""

def main():
    target_message = "abracadabra"
    assert len(SECRET) < 20, 'Secret too long'
    m = SECRET + target_message
    original_sig = hashlib.sha1(m.encode()).hexdigest()
    print(motd)
    print(f'The ancient seal reads: {original_sig}')
    print(f"Your incantation must weave the sacred word: {target_message}")
    print(f"But beware, only unique enchantments hold true power!")

    while True:
        user_message_h = input('Whisper your spell into the enchanted tome (hex): ')
        user_sig = input('Seal your magic with a sacred rune: ')

        user_message = bytes.fromhex(user_message_h)
        if user_message == b'abracadabra':
            print("A true sorcerer crafts spells with creativity and cunning!")
            continue

        if b'abracadabra' not in user_message:
            print("The arcane energies falter... your spell lacks the sacred word!")

        m = SECRET.encode() + user_message
        sig = hashlib.sha1(m).hexdigest()

        if sig == user_sig: 
            print(f'The enchantment is complete! The ancient forces bow to your mastery. You have unlocked the arcane secret: {FLAG}')
            return
        else:
            print("Your magic is close but lacks the true essence. Try again!")

        


if __name__ == '__main__':
    main()
