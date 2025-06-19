import Graph.*;
import Node.Tile;
import Node.TileConfig;
import Node.TxConfig;
import RoomGeometry.Room;
import RoomGeometry.RoomHandler;
import Helpers.JsonFileManager;

import java.io.File;

public class Main {

    public static void main(String[] args) {

        double frequency = 30e9;
        double c = 299792458;
        double wavelength = c / frequency;


        // Create Room
        double[] roomDims = new double[]{15, 10, 5}; // Room dimensions x,y,z
        int numSpheres = 5;
        double pathLossExponent = 3;
        RoomHandler roomHandler = new RoomHandler(); // Handles room creation (walls and obstacles)
        roomHandler.createCuboidRoom(roomDims);
        roomHandler.addSpheres(numSpheres);

        Room cuboidRoom = roomHandler.getRoom(); // Final room object. Input for graphs creation
        cuboidRoom.setAlpha(pathLossExponent);


        // Set transmitter parameters
        TxConfig txConfig = new TxConfig(160, 1, 0, wavelength);


        //Set SDM Parameters
        TileConfig tileConfig = new TileConfig(20, wavelength / 2, 4, wavelength);


        int[] numberOfTilesVector = {16};
        int[] numReceiversVector = {4};


        int numberOfGraphs = 1;
        String folderPath1 = "Graphs_" + (int) roomDims[0] + "x" + (int) roomDims[1] + "x" + (int) roomDims[2];
        File directory = new File(folderPath1);
        directory.mkdir();
        JsonFileManager jS = new JsonFileManager();
        for (int numberOfTiles : numberOfTilesVector) {

            for (int numReceivers : numReceiversVector) {

                cuboidRoom.setParameters(numberOfTiles, numReceivers); //Set parameters for room

                txConfig.setNumLobes(numReceivers);

                System.out.println(numberOfTiles + " - " + numReceivers);
                String folderPath2 = folderPath1 + "/Rx_" + numReceivers;
                directory = new File(folderPath2);
                directory.mkdir();
                String folderPath3 = folderPath2 + "/Tiles_" + numberOfTiles;
                directory = new File(folderPath3);
                directory.mkdir();

                int i = 0;
                while (i < numberOfGraphs) {

                    System.out.print("Creating Graph " + i + "...");
                    Graph g = new Graph(cuboidRoom, txConfig, tileConfig); //Create Graph

                    if (g.graphCreationAborted) continue;

                    jS.writeGraphToJson(g, folderPath3 + "/Graph" + "_" + i);
                    i++;

                }

            }
        }
    }
}



