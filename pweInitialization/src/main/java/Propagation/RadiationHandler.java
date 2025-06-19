package Propagation;

import java.util.*;

import Node.*;
import Graph.*;

public class RadiationHandler {

    private Graph g;

    public RadiationHandler(Graph g) {
        this.g = g;
    }

    public boolean createInputRays() { // Handles Transmitter Radiation. Creates Input Rays by picking edges that
        boolean transmitterBlocked = true;

        Node transmitter = g.getTx();
        List<Edge> outputEdges = new ArrayList<>(transmitter.getOutputEdges());

        int numLobesCreated = 0;
        System.out.println(outputEdges.size());
        while (numLobesCreated < g.txConfig.getNumLobes() && !outputEdges.isEmpty()) {

            Edge edgePicked = outputEdges.get(g.rand.nextInt(outputEdges.size()));

            outputEdges.remove(edgePicked);

            double rayPower = g.txConfig.getPower() * edgePicked.getPathLoss();

            Ray newRay = new Ray(rayPower, edgePicked, edgePicked.getDestNode_id());
            g.inputRays.add(newRay);
            numLobesCreated++;

        }


        // Removing edges that will not be used in the simulation significantly reduces exported data size
        //removeUnusedEdges(outputEdges);

        // If the desired number of lobes cannot be created due to Tx blockage abort process and
        // proceed to create another graph

        if (numLobesCreated < g.txConfig.getNumLobes()) return transmitterBlocked;

        return !transmitterBlocked;

    }


    public void removeUnusedEdges(List<Edge> outputEdges) {

        List<Tile> tiles = g.getTiles();

        for (Tile tile : tiles) {
            List<Edge> inputEdges = tile.getInputEdges();
            for (Edge outputEdge : outputEdges)
                inputEdges.removeIf(edge -> inputEdges.contains(outputEdge));
        }

    }


}
