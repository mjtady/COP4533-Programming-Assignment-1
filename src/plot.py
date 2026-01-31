import pandas as pan
import matplotlib.pyplot as pt

df = pan.read_csv('scalability.csv')
pt.title('Analysis of Scalability')
pt.figure(figsize=(12, 8))
pt.xlabel('n')
pt.ylabel('time (ms)')
pt.plot('n',df['matchingTime'], label='matchingTime')
pt.plot('n',df['verifyTime'], label='verifyTime')
pt.grid(True)
pt.legend()
pt.show()