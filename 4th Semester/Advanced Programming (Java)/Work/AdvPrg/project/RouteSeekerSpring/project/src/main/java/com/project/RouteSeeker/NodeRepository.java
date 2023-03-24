package com.project.RouteSeeker;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.repository.query.Param;
import java.util.List;

public interface NodeRepository extends JpaRepository<Node, Integer>{

    Node findNodeById(@Param("id") Integer id);
}
