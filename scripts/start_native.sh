# Active l'environement virtuel

DEBUG=0
PORT=2000
# choix du port
if [[ "$1" == "debug" ]]; then
    echo "Launch in debug mode"
    DEBUG=1
else
    echo "Launch in release mode"
    PORT=$(python -c "import random; print(random.randint(2000, 3000))")
fi

# Port du serial
# get serial port from config file
SERIAL=$(grep serial conf.properties | cut -d'=' -f2)

# stop the server and the viewer if they are running
python -m space_collector.killall &

if [ $DEBUG == 0 ]; then
    # Build the native code
    platformio run --environment native
fi
sleep 1

# start the server
python -m space_collector.game.server -p $PORT --timeout 5 &

sleep 3

# start the viewer / on small screens : --small-window
python -m space_collector.viewer -p $PORT --small-window &

sleep 3

if [ $DEBUG == 0 ]; then
    # Launch the native code with communication parameters
    ./.pio/build/native/program "localhost" $PORT "OrganisationKaotik"
fi
