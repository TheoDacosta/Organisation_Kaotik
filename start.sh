# Active l'environement virtuel

# choix du port
PORT=12345

# Port du serial
#SERIAL=COM8          # on Windows
SERIAL=/dev/ttyUSB0  # on Linux

# start the server
python -m space_collector.game.server -p $PORT --timeout 10 &

sleep 3

# start the viewer / on small screens : --small-window
python -m space_collector.viewer -p $PORT --small-window &

python -m space_collector.serial2tcp -p $PORT --serial $SERIAL --team-name "USS-Discovery"