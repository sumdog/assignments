#include <cnet.h>
#include <stdlib.h>
#include <string.h>

#define	MAXHOPS		4
#define	ALL_LINKS	(-1)

/*
    This file implements a much better flooding algorithm than those in
    both flooding1.c and flooding2.c. As network layer packets are processed,
    the information in their headers is used to update the NL table.
    For example, each packet's maxhops field is initially set to MAXHOPS
    but as the true distance between source and destination is learnt by
    the NL table, the maxhops field is set to this much smaller
    value.  Similarly, as a new minimum hop count is determined by the
    NL table, the "best" link providing this minimum count is
    remembered and used thereafter.

    The extended routine NL_stats() is now called for both data and
    acknowledgement packets and we even "steal" information from network
    layer packets that don't belong to us!

    I don't think it's a flooding algorithm any more Toto.

    This flooding algorithm exhibits an efficiency which improves over time
    (as the NL table "learns" more).  With the 7 nodes in the
    AUSTRALIA.MAP file, the initial efficiency is the same as that of
    flooding1.c (about 2%) but as the NL table improves, the
    efficiency rises to over 60%.

    Execute this protocol with the command:	cnet FLOODING3

    Working with cnet v2.0.3, Jan 20 2002.
*/


typedef enum    	{ NL_DATA, NL_ACK }   NL_PACKETKIND;

typedef struct {
    CnetAddr		src;
    CnetAddr		dest;
    NL_PACKETKIND	kind;      	/* only ever NL_DATA or NL_ACK */
    int			seqno;		/* 0, 1, 2, ... */
    int			hopsleft;	/* time to live */
    int			hopstaken;
    int			length;       	/* the length of the msg portion only */
    CnetInt64		timesent;	/* in microseconds */
    char		msg[MAX_MESSAGE_SIZE];
} NL_PACKET;

#define PACKET_HEADER_SIZE  (2*sizeof(CnetAddr)+sizeof(NL_PACKETKIND)+ \
				4*sizeof(int)+sizeof(CnetInt64))
#define PACKET_SIZE(p)	    (PACKET_HEADER_SIZE + p.length)


/* - A SIMPLE NETWORK LAYER TABLE AS AN ABSTRACT DATA TYPE (getting bigger) */


typedef struct {
    CnetAddr	address;
    int		ackexpected;
    int		nextpackettosend;
    int		packetexpected;
    long	minhops;
    long	minhop_link;
    CnetInt64	totaltime;
} NL_TABLE;

static	NL_TABLE	*table;
static	int		table_size;


static void init_NL()
{
    table	= (NL_TABLE *)malloc(sizeof(NL_TABLE));
    table_size	= 0;
}


static int find_address(CnetAddr address)
{
    int	t;

    for(t=0 ; t<table_size ; ++t)
	if(table[t].address == address)
	    return(t);

    table	= (NL_TABLE *)realloc((char *)table,
					(table_size+1)*sizeof(NL_TABLE));

    table[table_size].address		= address;
    table[table_size].ackexpected	= 0;
    table[table_size].nextpackettosend	= 0;
    table[table_size].packetexpected	= 0;
    table[table_size].minhops		= MAXHOPS;
    table[table_size].minhop_link	= 0;
    table[table_size].totaltime		= int64_ZERO;
    return(table_size++);
}

static int ackexpected(CnetAddr address) {
    return(table[ find_address(address) ].ackexpected);
}

static void inc_ackexpected(CnetAddr address) {
    table[ find_address(address) ].ackexpected++;
}

static int nextpackettosend(CnetAddr address) {
    return(table[ find_address(address) ].nextpackettosend++);
}

static int packetexpected(CnetAddr address) {
    return(table[ find_address(address) ].packetexpected);
}

static void inc_packetexpected(CnetAddr address) {
    table[ find_address(address) ].packetexpected++;
}

static int maxhops(CnetAddr address) {
    return(table[ find_address(address) ].minhops);
}

static int whichlink(CnetAddr address) {
    int link	= table[ find_address(address) ].minhop_link;
    return(link == 0 ? ALL_LINKS : (1 << link));
}

static void NL_stats(CnetAddr address, int hops, int link, CnetInt64 usec)
{
    int	t;

    t = find_address(address);
    if(table[t].minhops >= hops) {
	table[t].minhops	= hops;
	table[t].minhop_link	= link;
    }
    int64_ADD(table[t].totaltime, table[t].totaltime, usec);
}
			 
static void show_table(CnetEvent ev, CnetTimer timer, CnetData data)
{
    int	t, n;

    CNET_clear();
    printf("\n%14s %14s %14s %14s %14s\n",
    "destination","packets-ack'ed","min-hops","minhop-link", "round-trip-time");
    for(t=0 ; t<table_size ; ++t)
	if((n = table[t].ackexpected) > 0) {
	    CnetInt64	avtime;

	    int64_I2L(avtime, n);
	    int64_DIV(avtime, table[t].totaltime, avtime);
	    printf("%14d %14d %14ld %14ld %14s\n",
		    (int)table[t].address, table[t].ackexpected,
		    table[t].minhops, table[t].minhop_link,
		    int64_L2A(avtime,0));
	}
}


/** Sumit - Transport Layer   ----------------------------------*/

/* HEADER */
static void down_to_transport(CnetEvent ev, CnetTimer timer, CnetData data);

static void up_to_transport(char *msg, int *len, CnetAddr source);

static void down_to_network(char *msg,int length, CnetAddr dest);

typedef enum { ACK, NCK, MSG } tl_packet;

typedef struct {

  unsigned int checksum;
  unsigned int sequence_number;
  int length;
  tl_packet type;
  char msg[MAX_MESSAGE_SIZE];

} TR_PACKET;

#define TR_HEADER_SIZE     (sizeof(int)+ (sizeof(unsigned int)*2) + sizeof(tl_packet))
#define TR_PACKET_SIZE(p) (TR_HEADER_SIZE + p.length)

/* END PROTOTYPE HEADER */

static void up_to_transport(char *msg, int *len, CnetAddr source) {

  TR_PACKET *p;
  p = (TR_PACKET*) msg;
  
  if(p->type == MSG) {

      CHECK(CNET_write_application(p->msg,&(p->length)));

  }
  else if(p->type == ACK) {
  }
  else if(p->type == NCK) {
  }
  else {
    /* the type field is malformed...
       since we're not sure what this is suposte 
       to be..we'll just drop it and wait for it
       to come around again
    */
  }
  
}


static void down_to_transport(CnetEvent ev, CnetTimer timer, CnetData data) {

  /* our packet  */
  TR_PACKET p;

  /* destination address to pass to network layer */
  CnetAddr temp;


  p.type = MSG;
  p.length = sizeof(p.msg);
  CHECK(CNET_read_application(&temp, p.msg, &p.length));
  CNET_disable_application(temp);
  /* p.sequence_number = 0; */

  p.checksum = checksum_crc32( ((char*)&p)+sizeof(unsigned int) 
			       , TR_PACKET_SIZE(p) - sizeof(unsigned int));
  
  down_to_network( (char*)&p , TR_PACKET_SIZE(p) , temp);
}



/** end Transport------------------------------------------------------------*/




/* Network------------------------------------------------------------------- */

static int down_to_datalink(int link, char *packet, int length);

static void selective_flood(char *packet, int length, int links_wanted)
{
    int	   link;

    for(link=1 ; link<=nodeinfo.nlinks ; ++link)
	if( links_wanted & (1<<link) )
	    CHECK(down_to_datalink(link, packet, length));
}

static void down_to_network(char* msg, int length, CnetAddr dest)
{
  /* modified to take stuff form my transport layer
     instead of application layer -- Sumit*/
    NL_PACKET p;
    p.length = length;
    memcpy(&(p.msg[0]),msg,length);
  
    p.dest      = dest;
    p.src	= nodeinfo.address;
    p.kind	= NL_DATA;
    p.hopsleft	= maxhops(p.dest);
    p.hopstaken	= 1;
    p.timesent	= nodeinfo.time_in_usec;
    p.seqno	= nextpackettosend(p.dest);

    selective_flood((char *)&p, PACKET_SIZE(p), whichlink(p.dest));
}


static int up_to_network(char *packet, int length, int arrived_on)
{
    NL_PACKET	*p;
    CnetAddr	addr;

    p	= (NL_PACKET *)packet;

    if(p->dest == nodeinfo.address) {		/*  THIS PACKET IS FOR ME */
	if(p->kind == NL_DATA && p->seqno == packetexpected(p->src)) {
	    length	= p->length;
	    /* modified to go up to my transport layer instead */
	    /* of application i -- Sumit*/
	    up_to_transport(p->msg, &length, p->src);

	    inc_packetexpected(p->src);

	    NL_stats(p->src, p->hopstaken, arrived_on, 0);

	    addr	 = p->src;	/* transform NL_DATA into NL_ACK */
	    p->src	 = p->dest;
	    p->dest	 = addr;

	    p->kind	 = NL_ACK;
	    p->hopsleft	 = maxhops(p->dest);
	    p->hopstaken = 1;
	    p->length	 = 0;
	    selective_flood(packet, PACKET_HEADER_SIZE, whichlink(p->dest) );
	}
	else if(p->kind == NL_ACK && p->seqno == ackexpected(p->src)) {
	    CnetInt64	took;

	    /*move this to transport layeri -- Sumit*/
	    /*CNET_enable_application(p->src);*/
	    inc_ackexpected(p->src);
	    int64_SUB(took, nodeinfo.time_in_usec, p->timesent);
	    NL_stats(p->src, p->hopstaken, arrived_on, took);
	}
    }
    else {				/* THIS PACKET IS FOR SOMEONE ELSE */
	if(--p->hopsleft > 0) {		/* send it back out again */
	    p->hopstaken++;
	    NL_stats(p->src, p->hopstaken, arrived_on, 0);
	    selective_flood(packet, length,
				whichlink(p->dest) & ~(1<<arrived_on));
	}
    }
    return(0);
}

/* ------------- A MINIMAL RELIABLE DATALINK LAYER FOLLOWS -------------- */


typedef struct {
    /* as we use a reliable datalink, we don't need any other fields */
    char        packet[sizeof(NL_PACKET)];
} DLL_FRAME;


static int down_to_datalink(int link, char *packet, int length)
{
  /* changed this to unreliable Suimt */
    CHECK(CNET_write_physical(link, (char *)packet, &length));
    return(0);
}

static void up_to_datalink(CnetEvent ev, CnetTimer timer, CnetData data)
{
    DLL_FRAME	f;
    int		link, length;

    length	= sizeof(DLL_FRAME);
    CHECK(CNET_read_physical(&link, (char *)&f, &length));

    CHECK(up_to_network(f.packet, length, link));
}

static void init_DLL()
{
    /* nothing to do! */
}


/* ----------------------------------------------------------------------- */

void reboot_node(CnetEvent ev, CnetTimer timer, CnetData data)
{
    if(nodeinfo.nlinks > 32) {
	fprintf(stderr,"selective flooding will not work here\n");
	exit(1);
    }

    CHECK(CNET_set_handler(EV_APPLICATIONREADY, down_to_transport, 0));
    CHECK(CNET_set_handler(EV_PHYSICALREADY,    up_to_datalink, 0));
    CHECK(CNET_set_handler(EV_DEBUG1,           show_table, 0));

    CHECK(CNET_set_debug_string( EV_DEBUG1, "NL info"));

    init_DLL();
    init_NL();

    CNET_enable_application(ALLNODES);
}
