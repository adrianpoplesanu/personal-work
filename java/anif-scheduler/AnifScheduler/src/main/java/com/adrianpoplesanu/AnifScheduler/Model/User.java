package com.adrianpoplesanu.AnifScheduler.Model;

import javax.persistence.*;
import java.util.Date;

@Entity
@Table(name = "Users")
public class User {
    @Column
    @Id
    @GeneratedValue
    private int id;

    @Column
    private String firstname;

    @Column
    private String lastname;

    @Column
    private String email;

    @Column
    private String password;

    @Column(name = "createddate", insertable = false)
    @Temporal(TemporalType.TIMESTAMP)
    private Date createdDate;

    @Column(name = "modifieddate", insertable = false, updatable = false)
    @Temporal(TemporalType.TIMESTAMP)
    private Date modifiedDate;

}
