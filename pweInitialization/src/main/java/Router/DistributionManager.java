package Router;

import Graph.*;
import Node.*;

import java.util.*;

public class DistributionManager {


    private Graph g;
    private double[] distribution;
    private Hashtable<Edge, double[]> thetaPhiArchive;
    private static double DIFFUSION_GAIN = 0.05;


    public DistributionManager(Graph g) {
        this.g = g;
        thetaPhiArchive = new Hashtable<>();

    }

    public double[] getDistribution() {
        return distribution;
    }


    public void steer(Tile tile, Edge inputEdge) {
        int mean = 2 * g.room.getNumTiles() / 8;
        double stdDev = 0.5;
        int maxSize = (int) (mean + stdDev * g.rand.nextGaussian());

        List<Edge> outputEdges = new ArrayList<>(tile.getOutputEdges());
        //outputEdges.removeIf(edge -> Math.abs(tile.getPhiAngle(edge) - tile.getPhiAngle(inputEdge)) < Math.PI);
        Collections.shuffle(outputEdges);

        int distSize = Math.min(maxSize, outputEdges.size());
        // Array to store the final distributed values
        distribution = new double[distSize];
        int i = 0;
        while (i < distSize && !outputEdges.isEmpty()) {

            Edge outputEdge = outputEdges.get(g.rand.nextInt(outputEdges.size()));

            double incidentAngle = tile.getThetaAngle(inputEdge);
            double reflectedAngle = tile.getThetaAngle(outputEdge);

            double maxGain = Math.abs(Math.cos(reflectedAngle - incidentAngle));

            if (maxGain == 0) System.out.println(reflectedAngle + " " + incidentAngle);

            // Generate a normally distributed value with μ = 0.5 and σ = 0.15
            double randValue = g.rand.nextDouble(0.8);

            // Multiply by max gain
            distribution[i] = outputEdge.getId() + maxGain * randValue;
            outputEdges.remove(outputEdge);
            i++;
        }


    }


    public void diffuse(Tile tile, Edge inputEdge) {

        List<Edge> outputEdges = new ArrayList<>(tile.getOutputEdges());
        //outputEdges.removeIf(edge -> Math.abs(tile.getPhiAngle(edge) - tile.getPhiAngle(inputEdge)) < Math.PI);

        int distSize = tile.getOutputEdges().size();

        // Array to store the final distributed values
        distribution = new double[distSize];
        int i = 0;
        while (i < distSize && !outputEdges.isEmpty()) {

            Edge outputEdge = outputEdges.get(g.rand.nextInt(outputEdges.size()));
            double incidentAngle = tile.getThetaAngle(inputEdge);
            double reflectedAngle = tile.getThetaAngle(outputEdge);

            double maxGain = Math.abs(Math.cos(reflectedAngle - incidentAngle));
            if (maxGain == 0) System.out.println(reflectedAngle + " " + incidentAngle);


            double randValue = g.rand.nextDouble(0.8);

            // Multiply by max gain
            distribution[i] = outputEdge.getId() + randValue * maxGain * DIFFUSION_GAIN;
            i++;
        }




    }


}





