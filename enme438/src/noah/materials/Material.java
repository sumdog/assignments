/*
 * Created on Feb 17, 2005
 */
package noah.materials;

/**
 * @author skhanna
 */
public abstract class Material {

    public final double DENSITY, CONDUCTIVITY, SPECIFICHEAT;    
    /**
     * 
     */
    public Material(double density, double conductivity, double specificheat) {
        DENSITY = density;
        CONDUCTIVITY = conductivity;
        SPECIFICHEAT = specificheat;
    }

    
}
