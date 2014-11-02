#!/bin/bash

SOUND_DIR="/Applications/iMovie HD.app/Contents/Resources/Sound Effects/Skywalker Sound Effects/"

afplay "${SOUND_DIR}/Suspense.mp3" & 
sleep 5
afplay "${SOUND_DIR}/Coyote.mp3"
sleep 2
afplay "${SOUND_DIR}/Heartbeat.mp3" & 
afplay "${SOUND_DIR}/Cold Wind.mp3"
sleep 1
afplay "${SOUND_DIR}/Scary Accent.mp3" & 
sleep 2
afplay "${SOUND_DIR}/Thunder.mp3"

