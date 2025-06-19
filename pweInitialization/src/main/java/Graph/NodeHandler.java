package Graph;

import Helpers.VectorOperator;
import Node.*;
import RoomGeometry.*;

import java.util.ArrayList;
import java.util.List;

public class NodeHandler {

    Graph g;
    int nodeId = 0;

    public NodeHandler(Graph g) {
        this.g = g;
    }

    public void initializeNodes() {

        // Step 1: Distribute tiles to walls ensuring same density
        evenlyDistributeTileCounts();
        // Step 2: Randomly position tiles to walls ensuring far field approximations and no overlapping
        positionTiles();
        // Step 3: Randomly position users ensuring far field approximations
        positionReceivers();
        // Step 4: Randomly position Tx ensuring far field approximations
        positionTransmitter();

    }

    public void evenlyDistributeTileCounts() {
        List<Surface> surfaces = g.room.getSurfaces();
        double totalArea = g.room.getTotalArea();

        int assignedTiles = 0;
        double[] remainders = new double[surfaces.size()];

        // Step 2: Assign initial number of tiles and track remainders
        for (int i = 0; i < surfaces.size(); i++) {
            Surface sur = surfaces.get(i);
            double exactShare = (sur.getArea() / totalArea) * g.room.getNumTiles();
            int tiles = (int) Math.floor(exactShare);
            sur.setNumberOfTiles(tiles);
            assignedTiles += tiles;
            remainders[i] = exactShare - tiles;
        }

        // Step 3: Distribute remaining tiles based on largest remainders
        int remainingTiles = g.room.getNumTiles() - assignedTiles;
        while (remainingTiles > 0) {
            int maxIndex = -1;
            double maxRemainder = -1;
            for (int i = 0; i < remainders.length; i++) {
                if (remainders[i] > maxRemainder) {
                    maxRemainder = remainders[i];
                    maxIndex = i;
                }
            }
            if (maxIndex != -1) {
                Surface s = surfaces.get(maxIndex);
                s.setNumberOfTiles(s.getNumberOfTiles() + 1);
                remainders[maxIndex] = -1; // Avoid picking again
                remainingTiles--;
            } else {
                break; // failsafe
            }
        }
    }


    public void positionTiles() {
        Room room = g.room;
        // Set SDMs
        for (Surface sur : room.getSurfaces()) {
            List<Tile> surTiles = new ArrayList<>();
            int numberOfTilesCounter = 0;
            while (numberOfTilesCounter < sur.getNumberOfTiles()) {
                double tileX = 0, tileY = 0, tileZ = 0;
                switch (sur.getType()) {
                    case "XY" -> {
                        tileZ = sur.getD();
                        tileX = g.rand.nextDouble() * (sur.getXLims()[1] - sur.getXLims()[0]) + sur.getXLims()[0];
                        tileY = g.rand.nextDouble() * (sur.getYLims()[1] - sur.getYLims()[0]) + sur.getYLims()[0];
                    }
                    case "XZ" -> {
                        tileY = sur.getD();
                        tileX = g.rand.nextDouble() * (sur.getXLims()[1] - sur.getXLims()[0]) + sur.getXLims()[0];
                        tileZ = g.rand.nextDouble() * (sur.getZLims()[1] - sur.getZLims()[0]) + sur.getZLims()[0];
                    }
                    case "YZ" -> {
                        tileX = sur.getD();
                        tileY = g.rand.nextDouble() * (sur.getYLims()[1] - sur.getYLims()[0]) + sur.getYLims()[0];
                        tileZ = g.rand.nextDouble() * (sur.getZLims()[1] - sur.getZLims()[0]) + sur.getZLims()[0];
                    }
                    default -> System.out.println("ERROR : Surface not parallel to any of the XYZ planes");
                }

                // Create and add the tile
                Tile newTile = new Tile(nodeId, "Tile");
                newTile.setPosition(new double[]{tileX, tileY, tileZ});
                newTile.setN(sur.getN());
                newTile.setV(sur.getV());
                newTile.setU(sur.getU());

                if (isOverlapping(newTile, surTiles)) continue;
                if (inNearFieldDistance(newTile)) continue;

                g.allNodes.add(newTile);
                surTiles.add(newTile);
                numberOfTilesCounter++;
                nodeId++;

            }
        }
    }

    public void positionReceivers() {
        Room room = g.room;
        double roomX = room.getDims()[0];
        double roomY = room.getDims()[1];
        double roomZ = room.getDims()[2];

        // Set receivers
        for (int i = 0; i < g.room.getNumReceivers(); i++) {
            Node receiver = new Node("Rx");
            do {
                receiver.setPosition(new double[]{
                        g.rand.nextDouble() * roomX,
                        g.rand.nextDouble() * roomY,
                        g.rand.nextDouble() * roomZ}
                );
            } while (inNearFieldDistance(receiver));

            receiver.setId(nodeId++);
            g.allNodes.add(receiver);
        }
    }

    public void positionTransmitter() {
        Room room = g.room;
        double roomX = room.getDims()[0];
        double roomY = room.getDims()[1];
        double roomZ = room.getDims()[2];

        // Set transmitter
        Node transmitter = new Node("Tx");
        do {
            transmitter.setPosition(new double[]{
                    g.rand.nextDouble() * roomX,
                    g.rand.nextDouble() * roomY,
                    g.rand.nextDouble() * roomZ}
            );
        } while (inNearFieldDistance(transmitter));

        transmitter.setId(nodeId++);
        g.allNodes.add(transmitter);


    }


    public boolean inNearFieldDistance(Node newNode) { // Makes sure that a new node is positioned in far field distance

        for (Node node : g.allNodes) {
            if (g.areOnSameWall(newNode, node))
                continue; // If elements are on the same wall,ignore
            double distance = VectorOperator.distance(node.getPosition(), newNode.getPosition());
            if (distance < 2 * Math.pow(g.tileConfig.getMaxDim(), 2) / g.tileConfig.getWavelength()) return true;

        }
        return false;
    }

    public boolean isOverlapping(Tile newTile, List<Tile> surTiles) { // Makes sure tiles are not overlapping

        for (Tile tile : surTiles) {
            double distance = VectorOperator.distance(newTile.getPosition(), tile.getPosition());

            if (distance < g.tileConfig.getMaxDim()) return true;

        }
        return false;
    }

}
