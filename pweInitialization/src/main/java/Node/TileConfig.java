package Node;

public class TileConfig {

    private int numElements;
    private double elementSpacing;
    private double elementGain;
    private double maxGain;
    private double maxDim;
    private double wavelength;



    public TileConfig(int numElements, double elementSpacing, double elementGain, double wavelength) {
        this.numElements = numElements;
        this.elementSpacing = elementSpacing;
        this.elementGain = elementGain;
        this.maxGain = 10000 * elementGain * Math.pow(numElements, 2);
        this.maxDim = elementSpacing * numElements;
        this.wavelength = wavelength;

    }

    public double getMaxGain() {
        return maxGain;
    }

    public double getMaxDim(){
        return maxDim;
    }

    public double getWavelength(){
        return wavelength;
    }
}
