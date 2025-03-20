
# choix du port
PORT=$(python -c "import random; print(random.randint(2000, 3000))")

# Recuperation address
ADDRESS=$(grep address conf.properties | cut -d'=' -f2)

# stop the server and the viewer if they are running
python -m space_collector.killall &

# Build the native code
platformio run --environment native

sleep 1

# start the server
python -m space_collector.game.server -a $ADDRESS -p $PORT --timeout 5 &

sleep 3

# start the viewer / on small screens : --small-window
python -m space_collector.viewer -p $PORT --small-window &

sleep 3

# Launch the native code with communication parameters
./.pio/build/native/program $ADDRESS $PORT "OrganisationKaotik"
