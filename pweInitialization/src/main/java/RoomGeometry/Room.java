package RoomGeometry;

import java.util.ArrayList;
import java.util.List;

public class Room {

    private List<Surface> surfaces;
    private List<Obstacle> obstacles;
    private double[] dims;
    private double totalArea;
    private double alpha;
    private int numReceivers;
    private int numTiles;


    public Room() {
        surfaces = new ArrayList<>();
        obstacles = new ArrayList<>();
        dims = new double[3];


    }

    public void setParameters(int numTiles, int numReceivers) {
        this.numTiles = numTiles;
        this.numReceivers = numReceivers;
    }

    public void setNumTiles(int numTiles) {
        this.numTiles = numTiles;
    }

    public List<Surface> getSurfaces() {
        return surfaces;
    }

    public List<Obstacle> getObstacles() {
        return obstacles;
    }

    public double[] getDims() {
        return dims;
    }

    public void setDims(double[] dims) {
        this.dims = dims;
    }

    public double getTotalArea() {
        return totalArea;
    }

    public void setTotalArea(double totalArea) {
        this.totalArea = totalArea;
    }

    public double getAlpha() {
        return alpha;
    }

    public int getNumReceivers() {
        return numReceivers;
    }

    public int getNumTiles() {
        return numTiles;
    }

    public void addToSurfaces(Surface surface){surfaces.add(surface);

    }

    public void addToObstacles(Obstacle obst){obstacles.add(obst);

    }


    public void setAlpha(double alpha) {
        this.alpha = alpha;
    }
}
