#include <artnet/artnet.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

const int MAXCHANNELS=512;

static uint8_t dmx[MAXCHANNELS];
static artnet_node node;


int dmx_handler(artnet_node n, int prt , void *d ) {
        int len ;
        uint8_t *data ;


	printf("in handler\n");

        //CLogger logger (loglevel);

        //logger.log(ERROR,"dmx_handler: recieving DMX data");

        if( prt == 0 ) {
                data = artnet_read_dmx(n, prt, &len) ;
                memcpy(dmx, data,len) ;
                //logger.log(ERROR, "dmx_handler: %d", data[0]);
        }

        return 0 ;
}


int main( int argc, char** argv )
{

        int subnet_addr = 0 , port_addr = 0 ;
        int artnet_sd ;

	memset(dmx, 0x00, MAXCHANNELS) ;

        /* set up artnet node */
        node = artnet_new(NULL, 1);

        if(artnet_set_dmx_handler(node, dmx_handler, NULL) ) {
                //logger.log(ERROR, "main: Failed to install handler\n") ;
                return 1 ;
        }
        // set names and node type
        artnet_set_short_name(node, "DMX Test");
        artnet_set_long_name(node, "Artnet DMX Test");
        artnet_set_node_type(node, ARTNET_SRV);

        artnet_set_subnet_addr(node, subnet_addr);

    //    logger.log(INFO,"main: enabling DMX input\n");
        // enable the first input port (1 universe only)
        artnet_set_port_type(node, 0, ARTNET_ENABLE_OUTPUT, ARTNET_PORT_DMX);
        artnet_set_port_addr(node, 0, ARTNET_OUTPUT_PORT, port_addr);
        //  artnet_set_bcast_limit(node, 0);

    //    logger.log(INFO,"main: starting DMX node\n");
        //start the node
        artnet_start(node);


       // store the sds
        artnet_sd = artnet_get_sd(node);

        //logger.log(INFO, "main: ArtNet node config:");
        artnet_dump_config(node);

        //logger.log(INFO, "main: starting up");

        while (true) {

                artnet_read(node, 0);

                sleep(1);

		printf("DMX: %d\n", dmx[0]);

        }


}
