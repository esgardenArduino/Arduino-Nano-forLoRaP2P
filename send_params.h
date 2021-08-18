/*************************************************************************************/
/** ID_NODE **************************************************************************/
/*************************************************************************************/
#define INI_NODE 0
#define FIN_NODE 2

#define ID_NODE "01" // this code insertes values in the weather station space

// 01: "General"
// 02: "Nursery"
// 03: "Compost"
// 04: "Plot 1"
// 05: "Plot 2"
// 06: "Plot 3"
// 07: "Plot 4"
// 08: "Plot 5"
// 09: "Plot 6"
// 0A: "Plot 7"
// 0B: "Plot 8"

/************************************************************************************/
/** We must send a HEX string as follows:
 *  Characters 0,1: ID_NODE
 *  Nested string of tuples: TYPE + FIELD
 *  Where TYPE is 2 characters long; FIELD is 4 characters long
 ************************************************************************************/

#define SizeBuffer 28 // This example sends 4 sensor values; MAX 64; multiple of 4



/*************************************************************************************/
/** TYPES OF SENSORS SUPPORTED BY THE APP ********************************************/
/** For other purposes different than the APP, you can add or change values***********/
/*************************************************************************************/

#define INI_DATA 2
#define LON_TYPE 2
#define LON_VALUE 4

/***** TYPES ARE DEFINED IN THE APP; BE COHERENT *****************/
/***** THIS LIST CORRESPONDS WITH eSGarden APP PROJECT **********/
 
// TYPE 00: Brightness - 1 value
// TYPE 01: Temperature - 1 value
// TYPE 02: Humidity - 1 value
// TYPE 03: PH - 1 value
// TYPE 04: Relative noise - 1 value
// TYPE 05: Air Quality - 1 value
// TYPE 06: Rainfall - 1 value
// TYPE 07: Wind - 2 values
// TYPE 08: Soil temperature - 4 values
// TYPE 09: Soil humidity - 4 values

const int quantityOfVal[10] = {1,1,1,1,1,1,1,2,4,4};

/*************************************************************/
/** Add, remove or change depending on the sensors connected 
 * to your board ********************************************/
 
int TYPE0 = 05; //Example, CO2
int TYPE1 = 01; //Example, Ambient temperature
int TYPE2 = 02; //Example, Ambient humidity
int TYPE3 = 06; //Example, Brightness
//int TYPE4 = 07; //Example, Wind

int FIELD0 [1] = {};
int FIELD1 [1] = {};
int FIELD2 [1] = {};
int FIELD3 [1] = {}; 
//int FIELD4 [2] = {};

// Add as many as you need here; The number of "FIELDS" is the number of measures to be sent
