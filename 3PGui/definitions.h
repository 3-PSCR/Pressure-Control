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
const int numSeg = 3;
const int numCham = 9;                                                              // # chambers being controlled
int chamPump[numCham] = {P1, P1, P1, P2, P2, P2, P3, P3, P3};                       // Pump for each chamber
int findPump[numCham] = {0, 0, 0, 1, 1, 1, 2, 2, 2};                                // Lookup for the index of the chamber's pump in PWM / valvestate arrays
int otherCham[numCham][2] = {
  {1,2}, {0, 2}, {0, 1}, {4, 5}, {3, 5}, {3, 4}, {7, 8}, {6, 8}, {6, 7}
};                                                                                  // Lookup for the other chamber on the same pump
int setP[numCham] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};                           // Starting set pressure of each chamber
int status[numCham] = {LOK, LOK, LOK, LOK, LOK, LOK, LOK, LOK, LOK};                // Current status of each chamber
char valW[numCham] = {W11, W12, W13, W21, W22, W23, W31, W32, W33};                 // Chamber valve of each chamber
float chamPress[numCham];                                                           // Current pressure of each chamber
char pressV[numCham] = {
  Press10, Press10, Press10, Press20, Press20, Press20, Press30, Press30, Press30
  };                                                                                // Pre-pressure sensor for each chamber
char pressW[numCham] = {
  Press11, Press12, Press13, Press21, Press22, Press23, Press31, Press32, Press33
  };                                                                                // Pressure sensor for each chamber
char allP[numCham + numSeg] = {
  Press10, Press11, Press12, Press13, Press20, Press21, Press22, Press23, Press30, Press31, Press32, Press33
};
int valV[numSeg][2] = {{V11, V12}, {V21, V22}, {V31, V32}};                         // Pre-chamber valves of each pump

int PWM[numSeg];                                                                    // Current PWM value of each chamber
String valveState[numSeg];
// bool forceLOK[numCham];
int iPressure[numCham];
float pErr[numCham + numSeg];

int DoF;
int tic; 
int rawPressure;
float volt;
float pError;
