package com.project.RouteSeeker;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.repository.query.Param;

public interface EdgeRepository extends JpaRepository<Edge, Integer>{

    Node findNodeById(@Param("id") Integer id);
    Node findNodeBySrcAndDst(@Param("src") Integer src, @Param("dst")Integer dst);
}
