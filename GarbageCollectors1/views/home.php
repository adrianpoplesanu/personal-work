<html>
<head>
    <title>GarbageCollector ver 1.0</title>
    <link rel="stylesheet" href="<?php echo($ahost); ?>css/bootstrap.min.css">
    <link href="//netdna.bootstrapcdn.com/font-awesome/4.0.3/css/font-awesome.css" rel="stylesheet">
    <link rel="stylesheet" href="https://cdn.datatables.net/1.10.16/css/jquery.dataTables.min.css">
    <link rel="stylesheet" href="<?php echo($ahost); ?>css/index.css">
    <script src="<?php echo($ahost); ?>js/jquery.min.js"></script>
    <script src="<?php echo($ahost); ?>js/bootstrap.min.js"></script>
    <script src="https://cdn.datatables.net/1.10.16/js/jquery.dataTables.min.js"></script>
    <script src="<?php echo($ahost); ?>js/index.js"></script>
</head>
<body>
    <div class="container">
        <div align="right">
            Bine ai venit <?php echo($username);?>! Asta e homepage-ul.
            <a href="logout.php">Logout</a>
        </div>
        <nav class="navbar navbar-default" role="navigation">
            <div class="container-fluid">
                <!-- Brand and toggle get grouped for better mobile display -->
                <div class="navbar-header">
                    <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
                        <span class="sr-only">Toggle navigation</span>
                        <span class="icon-bar"></span>
                        <span class="icon-bar"></span>
                        <span class="icon-bar"></span>
                    </button>
                    <a class="navbar-brand" href="#">Brand</a>
                </div>

                <!-- Collect the nav links, forms, and other content for toggling -->
                <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
                    <ul class="nav navbar-nav">
                        <li class="active"><a href="#">Link</a></li>
                        <li><a href="#">Link</a></li>
                        <li class="dropdown">
                            <a href="#" id="search_term" class="dropdown-toggle" data-toggle="dropdown">Clienti <b class="caret"></b></a>
                            <ul class="dropdown-menu">
                                <li><a class="search_term_option" href="#">Adauga client</a></li>
                                <li><a class="search_term_option" href="#">Vezi toti clientii</a></li>
                                <li><a class="search_term_option" href="#">Nu mai stiu ce</a></li>
                                <li class="divider"></li>
                                <li><a class="search_term_option" href="#">Altceva</a></li>
                                <li class="divider"></li>
                                <li><a class="search_term_option" href="#">Orice</a></li>
                            </ul>
                        </li>
                    </ul>
                <form class="navbar-form navbar-left" role="search">
                    <div class="form-group">
                        <input type="text" class="form-control" placeholder="Valoare">
                    </div>
                    <button type="submit" class="btn btn-default">Cauta</button>
                </form>
                    <ul class="nav navbar-nav navbar-right">
                        <li><a href="#">Link</a></li>
                        <li class="dropdown">
                            <a href="#" class="dropdown-toggle" data-toggle="dropdown">Genereaza rapoarte <b class="caret"></b></a>
                            <ul class="dropdown-menu">
                                <li><a href="#">Raport intrari deseuri</a></li>
                                <li><a href="#">Raport iesiri deseuri</a></li>
                                <li><a href="#">Raport reciclatori</a></li>
                                <li class="divider"></li>
                                <li><a href="#">Formularul de mediu</a></li>
                            </ul>
                        </li>
                    </ul>
                </div><!-- /.navbar-collapse -->
            </div><!-- /.container-fluid -->
        </nav>
        <!-- s-a terminat navigareA -->
        <!-- content -->
        <table id="example" class="display" cellspacing="0" width="100%">
            <thead>
                <tr>
                    <th>Name</th>
                    <th>Position</th>
                    <th>Office</th>
                    <th>Age</th>
                    <th>Start date</th>
                    <th>Salary</th>
                </tr>
            </thead>
            <tfoot>
                <tr>
                    <th>Name</th>
                    <th>Position</th>
                    <th>Office</th>
                    <th>Age</th>
                    <th>Start date</th>
                    <th>Salary</th>
                </tr>
            </tfoot>
            <tbody>
                <tr>
                    <td>Tiger Nixon</td>
                    <td>System Architect</td>
                    <td>Edinburgh</td>
                    <td>61</td>
                    <td>2011/04/25</td>
                    <td>$320,800</td>
                </tr>
                <tr>
                    <td>Garrett Winters</td>
                    <td>Accountant</td>
                    <td>Tokyo</td>
                    <td>63</td>
                    <td>2011/07/25</td>
                    <td>$170,750</td>
                </tr>
                <tr>
                    <td>Ashton Cox</td>
                    <td>Junior Technical Author</td>
                    <td>San Francisco</td>
                    <td>66</td>
                    <td>2009/01/12</td>
                    <td>$86,000</td>
                </tr>
            </tbody>
        </table>
        <!-- END content -->
    </div>
</body>
</html>