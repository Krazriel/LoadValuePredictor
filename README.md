# Load Value Prediction
- To start using the predictor, run the makefile:
```
make
```
- Running the application
```
./loadsim -f [TRACE FILENAME] -t [THRESHOLD] (optional -o for output trace)
```
- Threshold Level: 0 = Simple Last Value Predictor
- Level > 0 = Last Value Predictor with Confidence
- Example Run (trace: 200K.txt, threshold: 10%)
```
./loadsim -f traces/200K.txt -t 0.1
```
- Output
```
LAST VALUE PREDICTOR
--------------------------------------------------
[THRESHOLD] : 10.00%
[PERCENTAGE OF TRACE PREDICTED] : 75.41%
[CORRECT] : 159075.00
[TOTAL] : 178780.00
[ACCURACY] : 88.98%
--------------------------------------------------
```
