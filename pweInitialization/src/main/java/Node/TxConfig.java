package Node;

public class TxConfig {

    private double gain;
    private double power;
    private int numLobes;
    private double wavelength;


    public TxConfig(double gain, double power, int numLobes, double wavelength) {
        this.gain = gain;
        this.power = power;
        this.numLobes = numLobes;
        this.wavelength = wavelength;
    }

    public double getGain() {
        return gain;
    }

    public double getPower() {
        return power;
    }

    public int getNumLobes() {
        return numLobes;
    }

    public double getWavelength() {
        return wavelength;
    }

    public void setNumLobes(int numLobes) {
        this.numLobes = numLobes;
    }
}
