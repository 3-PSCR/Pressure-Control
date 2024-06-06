/* Valve definitions */
// Segment 1
#define V11 52
#define V12 50
#define W11 48
#define W12 46
#define W13 44

// Segment 2
#define V21 53
#define V22 51
#define W21 49
#define W22 47
#define W23 45

// Segment 3
#define V31 43
#define V32 41
#define W31 39
#define W32 37
#define W33 35

/* Pump definitions */
#define P1 9
#define P2 10
#define P3 11

#define kI 0.05

/* Sensor definitions */
// Segment 1
#define Press10 A0
#define Press11 A3
#define Press12 A4
#define Press13 A5

// Segment 2
#define Press20 A1
#define Press21 A8
#define Press22 A9
#define Press23 A10

// Segment 3
#define Press30 A2
#define Press31 A11
#define Press32 A12
#define Press33 A13

/* Stepper Definitions */
#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 200

/* Status definitions */
#define DEF 0
#define CRE 1
#define INF 2
#define LOK 3

// Three Seg
const int numSeg = 1;
const int numCham = 1;                                                              // # chambers being controlled
int chamPump[numCham] = {P1};                       // Pump for each chamber
int findPump[numCham] = {0};                                // Lookup for the index of the chamber's pump in PWM / valvestate arrays
int otherCham[numCham][2] = {
  {1,2}
};                                                                                  // Lookup for the other chamber on the same pump
int setP[numCham] = {80};                           // Starting set pressure of each chamber
int status[numCham] = {INF};                // Current status of each chamber
char valW[numCham] = {W12};                 // Chamber valve of each chamber
float chamPress[numCham];                                                           // Current pressure of each chamber
char pressV[numCham] = {
  Press10
  };                                                                                // Pre-pressure sensor for each chamber
char pressW[numCham] = {
  Press12
  };                                                                                // Pressure sensor for each chamber
char allP[numCham + numSeg] = {
  Press10, Press12
};
int valV[numSeg][2] = {{V11, V12}};                         // Pre-chamber valves of each pump


int PWM[numSeg];                                                                    // Current PWM value of each chamber
String valveState[numSeg];

int iPressure[numCham];
float pErr[numCham + numSeg];

int tic; 
int rawPressure;
float volt;
float pError;
