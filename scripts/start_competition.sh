
# Recuperation configuration
PORT=$(grep port conf.properties | cut -d'=' -f2)
ADDRESS=$(grep address conf.properties | cut -d'=' -f2)

# stop the viewer if he is running
python -m space_collector.killall &

# Build the native code
platformio run --environment native

# start the viewer / on small screens : --small-window
python -m space_collector.viewer -a $ADDRESS -p $PORT --small-window &

sleep 3

# Launch the native code with communication parameters
./.pio/build/native/program $ADDRESS $PORT "OrganisationKaotik"
