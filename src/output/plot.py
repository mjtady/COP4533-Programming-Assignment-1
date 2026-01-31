import pandas as pan
import matplotlib.pyplot as pt

df = pan.read_csv('scalability.csv')
pt.title('Analysis of Scalability')
pt.figure(figsize=(12, 8))
pt.xlabel('n')
pt.ylabel('time (ms)')
pt.plot(df['n'],df['matchingTime'], label='matchingTime')
pt.plot(df['n'],df['verificationTime'], label='verifyTime')
pt.grid(True)
pt.legend()
pt.show()
