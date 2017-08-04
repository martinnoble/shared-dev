 
 
 /** RF24Mesh_Example_Master.ino by TMRh20
  * 
  * Note: This sketch only functions on -Arduino Due-
  *
  * This example sketch shows how to manually configure a node via RF24Mesh as a master node, which
  * will receive all data from sensor nodes.
  *
  * The nodes can change physical or logical position in the network, and reconnect through different
  * routing nodes as required. The master node manages the address assignments for the individual nodes
  * in a manner similar to DHCP.
  *
  */
  
#include "RF24Mesh/RF24Mesh.h"  
#include <RF24/RF24.h>
#include <RF24Network/RF24Network.h>

#define datasize 64

int fadeAmount = 5;

uint8_t dmxdata[datasize];


// RF24 radio(RPI_V2_GPIO_P1_15, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_8MHZ);  
RF24 radio(22, 0);
RF24Network network(radio);
RF24Mesh mesh(radio,network);

uint32_t displayTimer = 0;
uint32_t sendTimer = 0;

int main(int argc, char** argv) {
  
  // Set the nodeID to 0 for the master node
  mesh.setNodeID(0);
  // Connect to the mesh
  printf("start\n");
  mesh.begin();
  radio.printDetails();

  printf("Starting loop\n");

int i;
  for (i = 0; i < datasize; i = i + 1) {
    //dmxdata[i] = random(255);
  }

  dmxdata[0] = 0;

while(1)
{
   
 
  // Call network.update as usual to keep the network updated
  mesh.update();

  // In addition, keep the 'DHCP service' running on the master node so addresses will
  // be assigned to the sensor nodes
  mesh.DHCP();

  if(millis() - displayTimer > 5000){
    displayTimer = millis();
    printf("********Assigned Addresses********\n");
     for(int i=0; i<mesh.addrListTop; i++){
       printf("NodeID: %d RF24Network Address: 0%o\n", mesh.addrList[i].nodeID, mesh.addrList[i].address);
     }
    printf("**********************************\n");
  }


    if(millis() - sendTimer > 40){
    
    dmxdata[0] = dmxdata[0] + fadeAmount;

    // reverse the direction of the fading at the ends of the fade:
    if (dmxdata[0] <= 0 || dmxdata[0] >= 255) {
      fadeAmount = -fadeAmount;
      
    }
    
    for (int i = 0; i < mesh.addrListTop; i++) {
      
      RF24NetworkHeader header(mesh.addrList[i].address); //Constructing a header
      if (!network.write(header, &dmxdata, sizeof(dmxdata))) {
         printf("Send Fail\n");
      }
      
    }
    sendTimer = millis();
  }


    
  
  // Check for incoming data from the sensors
  while(network.available()){
    printf("rcv\n");
    RF24NetworkHeader header;
    network.peek(header);
    
    uint32_t dat=0;
    switch(header.type){
      // Display the incoming millis() values from the sensor nodes
      case 'M': network.read(header,&dat,sizeof(dat)); 
                printf("Rcv %u from 0%o\n",dat,header.from_node);
                 break;
      default:  network.read(header,0,0); 
                printf("Rcv bad type %d from 0%o\n",header.type,header.from_node); 
                break;
    }







  }
delay(2);
  }
return 0;
}

      
      
      
