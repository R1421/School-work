# Will download data from Huffington Post and save it as data.csv
# Run once before trying predict.py, but you shouldn't need to run it frequently.

from csv import DictWriter
import re

from pollster import Pollster
pollster = Pollster()

kDATE = re.compile("[0-9]*-[0-9][0-9]-[0-9][0-9]")
kFIELDS = ['YEAR', 'DATE', 'TOPIC', 'NAME', 'MOE', 'SUBPOP', 'SUBPOPID', 'CHOICE', 'PARTY', 'VALUE', 'OBS', 'STATE']

if __name__ == "__main__":
    o = DictWriter(open("data.csv", 'w'), kFIELDS)
    o.writeheader()
    for year in [2012, 2016]:
        line = {}
        line['YEAR'] = year
        entry = pollster.charts(topic='%i-president' % year)
        for chart in entry:
            for poll in chart.polls():
                line['DATE'] = kDATE.findall(str(poll))[-1]
                for question in poll.questions:
                    line['TOPIC'] = question['topic']
                    line['NAME'] = question['name']
                    line['STATE'] = question['state']
                    subpop_id = 0
                    for subpop in question['subpopulations']:
                        subpop_id += 1
                        line['SUBPOPID'] = subpop_id
                        line['SUBPOP'] = subpop['name']
                        line['MOE'] = subpop['margin_of_error']
                        line['OBS'] = subpop['observations']
                        for res in subpop['responses']:
                            line['CHOICE'] = res['choice']
                            line['VALUE'] = res['value']
                            line['PARTY'] = res['party']
                            o.writerow(line)
                        
                        
