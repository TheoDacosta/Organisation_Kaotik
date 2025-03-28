# Active l'environement virtuel

# choix du port
PORT=$(python -c "import random; print(random.randint(2000, 3000))")

# Port du serial
# get serial port from config file
SERIAL=$(grep serial conf.properties | cut -d'=' -f2)

# stop the server and the viewer if they are running
python -m space_collector.killall &

sleep 1

# start the server
python -m space_collector.game.server -p $PORT --timeout 10 &

sleep 3

# start the viewer / on small screens : --small-window
python -m space_collector.viewer -p $PORT --small-window &

# Communication en serie
python -m space_collector.serial2tcp -p $PORT --serial $SERIAL --team-name "OK"
