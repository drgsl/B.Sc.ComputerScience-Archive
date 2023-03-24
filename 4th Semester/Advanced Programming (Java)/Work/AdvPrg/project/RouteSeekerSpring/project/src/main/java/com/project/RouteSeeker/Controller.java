package com.project.RouteSeeker;

import lombok.val;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/nodes")
public class Controller {

    private NodeRepository nodeRepository;
    private EdgeRepository edgeRepository;


    Graph graph;

    @Autowired
    public Controller(NodeRepository nodeRepository, EdgeRepository edgeRepository) {
        this.nodeRepository = nodeRepository;
        this.edgeRepository = edgeRepository;
    }


    @PostMapping(consumes = "application/json")
    public ResponseEntity<String> findNode(@RequestBody Integer nodeId) {

        val nodes = nodeRepository.findAll();
        for(Node n: nodes) {
            graph.addNode(new Node(n.getId(),n.getX(),n.getY()));
        }

        val edges = edgeRepository.findAll();
        for(Edge e: edges) {
            graph.addEdge(new Edge(e.getSrc(), e.getDest(), e.getWeight()));
        }

        Solver.solve();
        Graph.setResultEdges(Solver.getCycleOfCost(12));

        MainFrame mainFrame = new MainFrame();
        mainFrame.setVisible(true);

        return new ResponseEntity<>("done", HttpStatus.OK);
    }



}
