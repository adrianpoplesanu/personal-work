package com.adrianpoplesanu.AnifScheduler.Model;

import javax.persistence.*;
import java.util.Date;

@Entity
@Table
public class Task {
    @Column
    @Id
    @GeneratedValue
    private int id;

    @Column
    private int userid;

    @Column
    private String description;

    @Column
    private String status;

    @Column
    private String seap_status;

    @Column(name = "createddate", insertable = false)
    @Temporal(TemporalType.TIMESTAMP)
    private Date createdDate;

    @Column(name = "modifieddate", insertable = false, updatable = false)
    @Temporal(TemporalType.TIMESTAMP)
    private Date modifiedDate;
}
