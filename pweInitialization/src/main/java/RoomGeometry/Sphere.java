package RoomGeometry;

public class Sphere extends Obstacle {
    private double[] center;
    private double radius;

    public Sphere(double[] position, double radius){

        this.center = position;
        this.radius = radius;

    }

    public double[] getCenter() {
        return center;
    }

    public double getRadius() {
        return radius;
    }

}
