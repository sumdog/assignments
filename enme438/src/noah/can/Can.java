/*
 * Created on Feb 17, 2005
 */
package noah.can;

import noah.materials.*;

/**
 * @author skhanna
 */
public class Can {

    
    protected Node[][][] nodes;
    
    public final int MAX_INT;
    
    //private double density, conductivity, specificheat, xspacing, yspacing, zspacing,
    //fourier, totaltime;
    
    Material air, aluminum, water;

    public int x,y,z;
    public double xspacing, yspacing, zspacing, fourier, totaltime, timeinterval, aspacing, fluid, height;
    
    private int getMaxIterations() {
      int a = getIteration(air);
      int b = getIteration(water);
      int c = getIteration(aluminum);
      if( a > b && a > c) { return a; }
      if( b > c ) { return b; }
      return c;
    }
    
    public Node[][][] getNodes() {
        return nodes;
    }
    
    private int getIteration(Material a) {
        
        //calculation for max iterations
        double fus = a.CONDUCTIVITY / (a.DENSITY * a.SPECIFICHEAT);
        
        double spacing;
        if( xspacing < zspacing) {
            spacing = xspacing;
        }
        else {
            spacing = zspacing;
        }
        
        timeinterval = (fourier * (spacing*spacing)) / fus; 
        
        double iter = (totaltime*60) / timeinterval;
        
        //max iterations
        return (int)iter;
    }
    
    private double fToKelvin(double d) {
        return ((d - 32) / 1.8) + 273.15;
    }
    
    /**
     * 
     */
    public Can(int x,int y,int z,
            double xspacing, double zspacing, double fourier,
            double totaltime, double aspacing, double intemp, double outtemp, double fluid) {
        
        //establish notes
        nodes = new Node[x][y][z];
              
        //initalize all nodes
        for(int xa=0; xa<nodes.length; xa++) {
            for(int ya=0; ya<nodes[xa].length; ya++){
                for(int za=0; za<nodes[xa][ya].length;za++) {
                    
                    nodes[xa][ya][za] = new Node();
                    if(xa == x-1 || za == 0 || za == z-1) {
                        nodes[xa][ya][za].setTemp(0,fToKelvin(outtemp));
                    }
                    else {
                        nodes[xa][ya][za].setTemp(0,fToKelvin(intemp));
                    }
                    
                }
            }
        }
            
        
        //set materials
        air = new Air();
        aluminum = new Aluminum();
        water = new Water();
        
        //set vars
        this.fluid = fluid;
        this.x = x;
        this.y = y;
        this.z = z;
        this.aspacing = aspacing;
        this.xspacing = xspacing / 39.37;
        //this.yspacing = yspacing;
        yspacing = 2 * Math.PI * xspacing * aspacing;
        this.zspacing = zspacing / 39.37;
        this.fourier = fourier;
        this.totaltime = totaltime;
        
        //fluid height
        //height = fluid * ((231 / 128) * (1/(Math.PI * Math.pow(1.295,2)))) * (1/39.37);
        height = (fluid * (231.0/128.0) * (1.0/(Math.PI*(1.295*1.295))) +0.005)* (1.0/39.37);
        
        //max iterations
        MAX_INT = getMaxIterations();
        calcindex = 0;
    }

    
    public int calcindex; 
    
    public void stepCalculation() {
        
        //fluid node height
        long fluidnode = Math.round(height/zspacing);
        
        
        for( int x=0; x<nodes.length; x++) {
            for(int y=0; y<nodes[x].length; y++) {
                for(int z=0; z<nodes[x][y].length; z++) {
                    //double previous = 0;
                    int pindex = 0, cindex = 0;                    
                    //int current = 0;
                    if( calcindex != 0 ) {
                      //previous = nodes[x][y][z].getTemp(calcindex % 3);
                      pindex = calcindex % 3;
                      cindex = (calcindex+1) % 3;
                      //current = (calcindex+1) % 3;
                    }
                    else {
                        //previous = nodes[x][y][z].getTemp(0);
                        pindex = 0;
                        cindex = 1;
                    }
                    
                    //EQ1a
                    if( x == 0 &&  z == 1 ) {
                        //nodes[x][y][z].setTemp(current,previous+600);
                        nodes[x][y][z].setTemp(cindex,eq1(x,y,z,pindex,aluminum,water));
                    }
                    //EQ1b
                    else if(x == 0 && z == this.z-2) {
                        nodes[x][y][z].setTemp(cindex,eq1(x,y,z,pindex,air,aluminum));
                        //nodes[x][y][z].setTemp(current,previous+500);  
                    }
                    //EQ1c
                    else if (  z == fluidnode  && x == 0) {
                        nodes[x][y][z].setTemp(cindex,eq1(x,y,z,pindex,water,air));
                        //nodes[x][y][z].setTemp(current,previous+900);
                    }
                    //EQ2a
                    else if( x == this.x-2 && z == 1) {
                        nodes[x][y][z].setTemp(cindex,eq2(x,y,z,pindex,aluminum,water));
                        //nodes[x][y][z].setTemp(current,previous+300);
                    }
                    //EQ2b
                    else if( x == this.x-2 && z == this.z-2) {
                        nodes[x][y][z].setTemp(cindex,eq2(x,y,z,pindex,aluminum,air));
                        //nodes[x][y][z].setTemp(current,previous+400);
                    }
                    //EQ3a
                    else if ( z == 1 &&  x <= this.x-3  && x >= 1) {
                        nodes[x][y][z].setTemp(cindex,eq3(x,y,z,pindex,aluminum,water));
                        //nodes[x][y][z].setTemp(current,previous+700);
                    }
                    //EQ3c
                    else if ( z == fluidnode && x <= this.x-3 && x >= 1 ) {
                        nodes[x][y][z].setTemp(cindex,eq3(x,y,z,pindex,water,air));
                        //nodes[x][y][z].setTemp(current,previous+2000);
                    }
                    //EQ3b
                    else if( z == this.z-2 && x >= 1 && x <= this.x-3) {
                        nodes[x][y][z].setTemp(cindex,eq3(x,y,z,pindex,air,aluminum));
                        //nodes[x][y][z].setTemp(current,previous+800);
                    }
                    //EQ4
                    else if ( z == fluidnode && x == this.x-2)  {
                        nodes[x][y][z].setTemp(cindex,eq4(x,y,z,pindex,aluminum,water,air));
                        //nodes[x][y][z].setTemp(current,previous+1000);
                    }
                    //EQ5a
                    else if ( z < fluidnode && z > 1 && x == 0) {
                        nodes[x][y][z].setTemp(cindex,eq5(x,y,z,pindex,water));
                        //nodes[x][y][z].setTemp(current,previous+3000);
                    }
                    //EQ5b
                    else if ( z > fluidnode && z < this.z-2 && x == 0  ) {
                        nodes[x][y][z].setTemp(cindex,eq5(x,y,z,pindex,air));
                        //nodes[x][y][z].setTemp(current,previous+3500);
                    }
                    //EQ6a
                    else if ( z < fluidnode && z > 1 && x == this.x-2 ) {
                        nodes[x][y][z].setTemp(cindex,eq6(x,y,z,pindex,aluminum,water));
                        //nodes[x][y][z].setTemp(current,previous+3800);
                    }
                    //EQ6b
                    else if ( z > fluidnode && z < this.z-2 && x == this.x-2 ) {
                        nodes[x][y][z].setTemp(cindex,eq6(x,y,z,pindex,aluminum,air));
                        //nodes[x][y][z].setTemp(current,previous+4000);
                    }
                    //EQ7a
                    else if ( x > 0 && x < this.x-2 && z < fluidnode && z > 1 ) {
                        nodes[x][y][z].setTemp(cindex,eq7(x,y,z,pindex,water));
                        //nodes[x][y][z].setTemp(current,previous+7000);
                    }
                    //EQ7b
                    else if ( x > 0 && x < this.x-2 && z > fluidnode && z < this.z-2) {
                        nodes[x][y][z].setTemp(cindex,eq7(x,y,z,pindex,air));
                        //nodes[x][y][z].setTemp(current,previous+9000);
                    }
                    else {
                        nodes[x][y][z].setTemp(cindex,nodes[x][y][z].getTemp(pindex));
                    }
                    
                }
            }
        }
        calcindex++;
    }
    
    
    private double TARRAY(int x, int y, int z, int t) {
        
        //if(y == -1) { y = this.y-1; }
        //if(y == this.y) { y = 0; }
        
        return nodes[x][y][z].getTemp(calcindex);
    }
    /*
     * T(x,y,z,t+ti)=((ti*(k1+k2)*(x+0.5)*(TARRAY(x+1,y,z,t)-TARRAY(x,y,z,t)))/(x*(xspace^2)*(p1*c1+p2*c2)))+TARRAY(x,y,z,t)
     */
    public double eq1(int x, int y, int z, int t, Material k1, Material k2) {
       //((timeinterval*(k1.CONDUCTIVITY+k2.CONDUCTIVITY)*(x+0.5)*
                //(TARRAY(x+1,y,z,t)-TARRAY(x,y,z,t)))/(x*(Math.pow(xspacing,2))*
                //(k1.DENSITY*k1.SPECIFICHEAT+k2.DENSITY*k2.SPECIFICHEAT)))+TARRAY(x,y,z,t);
        
                //((timeinterval*(k1.CONDUCTIVITY+k2.CONDUCTIVITY)*(x+0.5)*
                //(TARRAY(x+1,y,z,t)-TARRAY(x,y,z,t)))/((x+0.5)*(Math.pow(xspacing,2))*
                //(k1.DENSITY*k1.SPECIFICHEAT+k2.DENSITY*k2.SPECIFICHEAT)))+TARRAY(x,y,z,t);
        
        return (TARRAY(x+1,y,z,t));
        
    }
    
    public double eq2(int x, int y, int z, int t, Material k1, Material k2) {
        return ((timeinterval)/(k1.DENSITY*k1.SPECIFICHEAT*(3*x+0.25)+k2.DENSITY*k2.SPECIFICHEAT*(x-0.25)))*
               ((((k1.CONDUCTIVITY+k2.CONDUCTIVITY)/(Math.pow(xspacing,2)))*
                (2)*(x-0.5)*(TARRAY(x-1,y,z,t)-TARRAY(x,y,z,t)))+(((k1.CONDUCTIVITY)/(Math.pow(xspacing,2)))*
                (4)*(x+0.5)*(TARRAY(x+1,y,z,t)-TARRAY(x,y,z,t)))+(((k1.CONDUCTIVITY+3*k2.CONDUCTIVITY)/
                (2*x*Math.PI*yspacing*xspacing*aspacing))*(TARRAY(x,y,z,t)-TARRAY(x,y,z,t)))+
                (((k1.CONDUCTIVITY+3*k2.CONDUCTIVITY)/(2*x*Math.PI*yspacing*xspacing*aspacing))*(TARRAY(x,y,z,t)-TARRAY(x,y,z,t)))+
                (((k1.CONDUCTIVITY)/(Math.pow(zspacing,2)))*(4*x)*(TARRAY(x,y,z-1,t)-TARRAY(x,y,z,t)))+(2)*(((k2.CONDUCTIVITY*(x-0.25)+
                k1.CONDUCTIVITY*(x+0.25))/(Math.pow(zspacing,2)))*(TARRAY(x,y,z+1,t)-TARRAY(x,y,z,t))))+TARRAY(x,y,z,t);
    }
    
    public double eq3(int x, int y, int z, int t, Material k1, Material k2) {
        return ((timeinterval)/(k1.DENSITY*k1.SPECIFICHEAT+k2.DENSITY*k2.SPECIFICHEAT))*
        ((((k1.CONDUCTIVITY+k2.CONDUCTIVITY)/(x*Math.pow(xspacing,2)))*(x-0.5)*(TARRAY(x-1,y,z,t)-
        TARRAY(x,y,z,t)))+(((k1.CONDUCTIVITY+k2.CONDUCTIVITY)/(x*Math.pow(xspacing,2)))*
        (x+0.5)*(TARRAY(x+1,y,z,t)-TARRAY(x,y,z,t)))+(((k2.CONDUCTIVITY+k1.CONDUCTIVITY)/
        (2*Math.PI*yspacing*xspacing*Math.pow(x,2)*aspacing))*(TARRAY(x,y,z,t)-TARRAY(x,y,z,t)))+
        (((k2.CONDUCTIVITY+k1.CONDUCTIVITY)/(2*Math.PI*yspacing*xspacing*(Math.pow(x,2))*aspacing))*
        (TARRAY(x,y,z,t)-TARRAY(x,y,z,t)))+(((k1.CONDUCTIVITY)/(Math.pow(zspacing,2)))*
        (TARRAY(x,y,z-1,t)-TARRAY(x,y,z,t)))+((k2.CONDUCTIVITY)/(Math.pow(zspacing,2)))*(TARRAY(x,y,z+1,t)-
        TARRAY(x,y,z,t)))+TARRAY(x,y,z,t);

    }
    
    public double eq4(int x, int y, int z, int t, Material k1, Material k2, Material k3) {
        return ((timeinterval)/(k1.DENSITY*k1.SPECIFICHEAT*(x+0.25)+k2.DENSITY*k2.SPECIFICHEAT*
               (x-0.25)+k3.DENSITY*k3.SPECIFICHEAT*(x-0.25)))*((((k1.CONDUCTIVITY+k2.CONDUCTIVITY)/
               (Math.pow(xspacing,2)))*(2)*(x-0.5)*(TARRAY(x-1,y,z,t)-TARRAY(x,y,z,t)))+
               (((k1.CONDUCTIVITY)/(Math.pow(xspacing,2)))*(4)*(x+0.5)*(TARRAY(x+1,y,z,t)-
               TARRAY(x,y,z,t)))+(((2*k1.CONDUCTIVITY+k2.CONDUCTIVITY+k3.CONDUCTIVITY)/
               (2*x*Math.PI*yspacing*xspacing*aspacing))*(TARRAY(x,y,z,t)-TARRAY(x,y,z,t)))+
               (((2*k1.CONDUCTIVITY+k2.CONDUCTIVITY+k3.CONDUCTIVITY)/(2*x*Math.PI*yspacing*xspacing*aspacing))*
               (TARRAY(x,y,z,t)-TARRAY(x,y,z,t)))+(((k2.CONDUCTIVITY*(x-0.25)+k1.CONDUCTIVITY*
               (x+0.25))/(Math.pow(zspacing,2)))*(2)*(TARRAY(x,y,z-1,t)-TARRAY(x,y,z,t)))+(2)*
               (((k3.CONDUCTIVITY*(x-0.25)+k1.CONDUCTIVITY*(x+0.25))/(Math.pow(zspacing,2)))*
               (TARRAY(x,y,z+1,t)-TARRAY(x,y,z,t))))+TARRAY(x,y,z,t);
    }

    public double eq5(int x, int y, int z, int t, Material k1) {
    	//((timeinterval*k1.CONDUCTIVITY*(x+0.5)*(TARRAY(x+1,y,z,t)-TARRAY(x,y,z,t)))/
        //(x*(Math.pow(xspacing,2))*(k1.DENSITY*k1.SPECIFICHEAT)))+TARRAY(x,y,z,t);
    	
        return (TARRAY(x+1,y,z,t));
    }

    public double eq6(int x, int y, int z, int t, Material k1, Material k2) {
        return ((timeinterval)/(k1.DENSITY*k1.SPECIFICHEAT*(x+0.25)+k2.DENSITY*
               k2.SPECIFICHEAT*(x-0.25)))*((((2*k2.CONDUCTIVITY)/(Math.pow(xspacing,2)))*
               (x-0.5)*(TARRAY(x-1,y,z,t)-TARRAY(x,y,z,t)))+(((k2.CONDUCTIVITY+k1.CONDUCTIVITY)/
               (Math.pow(xspacing,2)))*(x+0.5)*(TARRAY(x+1,y,z,t)-TARRAY(x,y,z,t)))+
               (((k2.CONDUCTIVITY+k1.CONDUCTIVITY)/(2*Math.PI*yspacing*xspacing*x*aspacing))
               *(TARRAY(x,y,z,t)-TARRAY(x,y,z,t)))+(((k2.CONDUCTIVITY+k1.CONDUCTIVITY)/
               (2*Math.PI*yspacing*xspacing*x*aspacing))*(TARRAY(x,y,z,t)-TARRAY(x,y,z,t)))+
               (((k2.CONDUCTIVITY*(x-0.25)+k1.CONDUCTIVITY*(x+0.25))/(Math.pow(zspacing,2)))*
               (TARRAY(x,y,z-1,t)-TARRAY(x,y,z,t)))+(((k2.CONDUCTIVITY*(x-0.25)+k1.CONDUCTIVITY*
               (x+0.25))/(Math.pow(zspacing,2)))*(TARRAY(x,y,z+1,t)-TARRAY(x,y,z,t))))
               +TARRAY(x,y,z,t);

    }
    
    public double eq7(int x, int y, int z, int t, Material k1) {
        return ((timeinterval)/(k1.DENSITY*k1.SPECIFICHEAT))*((((2*k1.CONDUCTIVITY)/
               (x*Math.pow(xspacing,2)))*(x-0.5)*(TARRAY(x-1,y,z,t)-TARRAY(x,y,z,t)))+
               (((2*k1.CONDUCTIVITY)/(x*Math.pow(xspacing,2)))*(x+0.5)*(TARRAY(x+1,y,z,t)-
               TARRAY(x,y,z,t)))+(((k1.CONDUCTIVITY)/(2*Math.PI*yspacing*xspacing*
               (Math.pow(x,2))*aspacing))*(TARRAY(x,y,z,t)-TARRAY(x,y,z,t)))+
               (((k1.CONDUCTIVITY)/(2*Math.PI*yspacing*xspacing*(Math.pow(x,2))*aspacing))*
               (TARRAY(x,y,z,t)-TARRAY(x,y,z,t)))+(((k1.CONDUCTIVITY)/(Math.pow(zspacing,2)))*
               (TARRAY(x,y,z-1,t)-TARRAY(x,y,z,t)))+((k1.CONDUCTIVITY)/(Math.pow(zspacing,2)))*
               (TARRAY(x,y,z+1,t)-TARRAY(x,y,z,t)))+TARRAY(x,y,z,t);
    }
}

