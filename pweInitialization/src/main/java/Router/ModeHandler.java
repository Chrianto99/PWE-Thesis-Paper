package Router;


import java.util.*;

import Graph.*;
import Helpers.*;
import Node.*;

public class ModeHandler {

    Graph g;
    DistributionManager distributionManager;
    static double DIFFUSION_CHANCE = 0.5;


    public ModeHandler(Graph g) {

        this.g = g;
        distributionManager = new DistributionManager(g);

    }

    public boolean initializeRoutingTables() {

        boolean abort = true;
        ArrayList<Tile> tiles = g.getTiles();

        for (Tile tile : tiles) {

            if (tile.getInputEdges().isEmpty()) {

                return abort;
            }
            tile.setNumberOfModes(g.numberOfModes);
            generateThetaPhiArchive(tile);

            for (Edge inputEdge : tile.getInputEdges()) {

                VectorOperator.reverseVector(inputEdge.getVector()); // Angles should be calculated from a common reference point

                createModes(inputEdge, tile); // create all modes for one input link

                VectorOperator.reverseVector(inputEdge.getVector()); // restore original vector to avoid confusions

            }


        }
        return !abort;


    }

    private void createModes(Edge inputEdge, Tile tile) {

        for (int i = 0; i < g.numberOfModes; i++) {
            if (g.rand.nextDouble() > DIFFUSION_CHANCE)
                distributionManager.steer(tile, inputEdge);
            else
                distributionManager.diffuse(tile, inputEdge);

            String key = inputEdge.getId() + " " + i;

            tile.addKvpToRoutingTable(key,distributionManager.getDistribution());


        }


    }

    public void generateThetaPhiArchive(Tile tile) {

        for (Edge edge : tile.getInputEdges()) {
            double theta = VectorOperator.calculateAngle(edge.getVector(), tile.getN());
            double phi = VectorOperator.calculatePhiAngle(tile.getN(), tile.getV(), tile.getU(), edge.getVector());
            tile.getThetaPhiArchive().put(edge, new double[]{theta, phi});
        }

        for (Edge edge : tile.getOutputEdges()) {
            double theta = VectorOperator.calculateAngle(edge.getVector(), tile.getN());
            double phi = VectorOperator.calculatePhiAngle(tile.getN(), tile.getV(), tile.getU(), edge.getVector());
            tile.getThetaPhiArchive().put(edge, new double[]{theta, phi});
        }
    }


}




