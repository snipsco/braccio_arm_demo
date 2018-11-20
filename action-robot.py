#!/usr/bin/env python2
# -*-: coding utf-8 -*-

# interface entre Snips et le code qui fait le taff coffeehack.py

# sert a lire le fichier config.init
'''import ConfigParser '''
''' nom de mon fichier  '''
from robotarm.robotarm import Robotarm
from hermes_python.hermes import Hermes
''' lecture ecriture sur fichier  '''
import io
import Queue
import threading

''' basique config '''

CONFIGURATION_ENCODING_FORMAT = "utf-8"
CONFIG_INI = "config.ini"

MQTT_IP_ADDR = "localhost"
MQTT_PORT = 1883
MQTT_ADDR = "{}:{}".format(MQTT_IP_ADDR, str(MQTT_PORT))




class Skill:

    def __init__(self):
        '''config = read_configuration_file("config.ini")
        extra = config["global"].get("extra", False)'''
        # .coffee est une variable je peux l'appeler comme je veux, coffeehack
        # est le nom de l'autre fichier
        self.started = 0
        self.robot = Robotarm()

# fonction pour ectraire la valeur d'un slot value
def extract_value(val):
    res = []
    if val is not None:
        for r in val:
            res.append(r.slot_value.value.value)
    return res

# tous les slots de l'app, extrait la valeur grace a la fonction au dessus,
# renvoit une liste

# def extract_coffee_size(intent_message):
#    return extract_value(intent_message.slots.coffee_size)

def extract_go_left(intent_message):
    goleft = intent_message.slots.Degrees.first().value
    # ou goleft = extract_value(intent_message.slots.Degrees)
    #ici on mets le slot dans une variable (non float)
    return int(goleft)

def extract_go_right(intent_message):
   goright = intent_message.slots.Degrees.first().value
   return int(goright)



# fonction qui est appele a chaque "pour" et qui va utiliser les methodes
# au dessus et la mets dans une variable.

#def coffee_steam(hermes, intent_message):
      #hermes.skill.coffee.steam()
def go_left_base(hermes, intent_message):
      leftbase = extract_go_left(intent_message)
      if hermes.skill.started == 0:
       return
      hermes.publish_end_session(intent_message.session_id, "")
      hermes.skill.robot.go_left_base(leftbase)

def go_right_base(hermes, intent_message):
     rightbase = extract_go_right(intent_message)
     if hermes.skill.started == 0:
       return
     hermes.publish_end_session(intent_message.session_id, "")
     hermes.skill.robot.go_right_base(rightbase)

#def open_grip(hermes, intent_message):
     #hermes.publish_end_session(intent_message.session_id, "")
     #hermes.skill.robot.open_grip()

def close_grip(hermes, intent_message):
     hermes.publish_end_session(intent_message.session_id, "")
     if hermes.skill.started == 0:
       return
     hermes.skill.robot.close_grip()

def start_game(hermes, intent_message):
     hermes.publish_end_session(intent_message.session_id, "")
     if hermes.skill.started == 1:
      return
     hermes.skill.started = 1
     timer = threading.Timer(60, reset_game, [hermes])
     timer.start()
     hermes.publish_start_session_notification("default", "C'est parti, vous avez une minute, bon courage!", "")

def reset_game(hermes):
     hermes.skill.started = 0
     hermes.publish_start_session_notification("default", "Vous avez perdu, une prochaine fois peut etre", "")

def return_position(hermes, intent_message):
     hermes.publish_end_session(intent_message.session_id, "")
     if hermes.skill.started == 0:
       return
     hermes.skill.robot.return_position()

def taking_ball(hermes, intent_message):
     hermes.publish_end_session(intent_message.session_id, "")
     if hermes.skill.started == 0:
       return
     hermes.skill.robot.taking_ball()

def dance(hermes, intent_message):
     hermes.publish_end_session(intent_message.session_id, "")
     if hermes.skill.started == 0:
       return
     hermes.skill.robot.dance()

def release_ball(hermes, intent_message):
     hermes.publish_end_session(intent_message.session_id, "")
     if hermes.skill.started == 0:
       return
     hermes.skill.robot.release_ball()

#def basket()


# a laisser
if __name__ == "__main__":
    skill = Skill()
    with Hermes(MQTT_ADDR) as h:
        h.skill = skill
        # nom de l'intent, nom de la fonction.
        h.subscribe_intent("valf:GoLeft", go_left_base) \
                .subscribe_intent("valf:GoRight", go_right_base) \
                .subscribe_intent("valf:CloseGrip", close_grip) \
                .subscribe_intent("valf:ReturnToPosition", return_position) \
                .subscribe_intent("valf:TakingBall", taking_ball) \
                .subscribe_intent("valf:Dance", dance) \
                .subscribe_intent("valf:ReleaseBall", release_ball) \
                .subscribe_intent("valf:StartGame", start_game) \
         .loop_forever()
