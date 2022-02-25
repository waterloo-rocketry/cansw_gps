#
# Converts GPS CAN messages produced by parsely in the form of
#
# [ GPS_TIMESTAMP             GPS        ] t=   417780ms	0hrs                72mins              2.0s                
# [ GPS_LATITUDE              GPS        ] t=   417793ms	43deg               28.3740mins         N                   
# [ GPS_LONGITUDE             GPS        ] t=   417806ms	80deg               32.4074mins         W                   
# [ GPS_INFO                  GPS        ] t=   417810ms	#SAT=6              QUALITY=1           
# [ GPS_ALTITUDE              GPS        ] t=   417824ms	322.160             M                   
#
# Into csv format, which can be visualized on https://www.gpsvisualizer.com/
#
import sys, re

class Info:
    def __init__(self):
        self.timestamp = None
        self.alt = None
        self.lat = None
        self.lon = None

    def _to_deg(self, deg, mins):
        degs = int(re.search('\d+', deg)[0])
        mins = float(re.search('[\d.]+', mins)[0])
        return degs + mins / 60

    def reset(self, t):
        self.timestamp = int(re.search('\d+', t)[0]) / 1000
        self.alt = None
        self.lat = None
        self.lon = None

    def set_alt(self, alt):
        self.alt = float(re.search('[\d.]+', alt)[0])

    def set_lat(self, deg, mins, direction):
        self.lat = self._to_deg(deg, mins)
        if direction == 'S':
            self.lat = -self.lat

    def set_lon(self, deg, mins, direction):
        self.lon = self._to_deg(deg, mins)
        if direction == 'W':
            self.lon = -self.lon

    def filled(self):
        return (
            self.timestamp is not None and
            self.alt is not None and
            self.lat is not None and
            self.lon is not None
        )

    def print_header(self):
        print(f'timestamp, alt, lat, lon')

    def print(self):
        print(f'{self.timestamp}, {self.alt}, {self.lat}, {self.lon}')

info = Info()
info.print_header()

for line in sys.stdin.readlines():
    fields = re.split(r'[\[\] \t]+', line.strip(' [\r\n'))

    if fields[0] == 'GPS_TIMESTAMP':
        info.reset(fields[3])
    elif fields[0] == 'GPS_ALTITUDE':
        info.set_alt(fields[4])
    elif fields[0] == 'GPS_LATITUDE':
        info.set_lat(fields[4], fields[5], fields[6])
    elif fields[0] == 'GPS_LONGITUDE':
        info.set_lon(fields[4], fields[5], fields[6])

    if info.filled():
        info.print()
