### Rock paper scissors test game ###

###imports
import random
import sys

###
print('Rock-Paper-Scissors Game\n')
print('rules: There are no rules\n')

a_action='dummy'
b_action=0
a_score=0
b_score=0

def get_action():
    result = raw_input()
    return result
#
def calc(a,b):
    if (a == b):
        print('TIE')
    elif (a == b+1 or a== b-2):
        print('LOSE')
    elif (b == a+1 or b== a-2):
        print('WIN')
#

while True:
    print('Choose Your Hand:\nLazor(1), Gun(2), Sword(3)')
    try:
        a_action = int(get_action())
    #
    except:
        ValueError
        a_action = 'dummy'
    #
    
    while( (not isinstance(a_action, int)) or a_action<=0 or a_action>=4 ):
        print('Bad Input; Try Again\nLazor(1), Gun(2), Sword(3)')
        try:
            a_action = int(get_action())
        #
        except:
            ValueError
            a_action = 'dummy'
        #
    #
    
    b_action = random.randint(1,3)

    if(a_action ==1):
        print('Lazor')
    elif(a_action==2):
        print('Gun')
    else:
        print('Sword')

    print(' vs ')

    if(b_action ==1):
        print('Lazor')
    elif(b_action==2):
        print('Gun')
    else:
        print('Sword')

    calc(a_action, b_action)

    print()
#
