function _b435566cbb42a3cfbe4bbe85e02a7ce6dd91a3cd(){};function _71a6d399c8be32c5c80f47049af7efbfdf58632a(){};function _db5e12b9bc5ff06dd0272b84916de9794c90de74(){};function _030ab66993ef3dc885136edba5367ebbc28a390e(){};function _d5dc28d1244acb1f6a053f4c2a930c6a7718d0d9(){};function _22505e5348c50548ec06273de4ddd2675f719420(){};function _c1a90f6e40d9b658422421440132a30a1bea6ec2(){};function _bdd3d09fd15dd10fb636df2cb199227056deb4c1(){};function _daa309d86a0be075629b3aafa0c6cb335512593e(){};/*
    This file is generated and updated by Sencha Cmd. You can edit this file as
    needed for your application, but these edits will have to be merged by
    Sencha Cmd when it performs code generation tasks such as generating new
    models, controllers or views and when running "sencha app upgrade".

    Ideally changes to this file would be limited and most work would be done
    in other places (such as Controllers). If Sencha Cmd cannot merge your
    changes and its generated code, it will produce a "merge conflict" that you
    will need to resolve manually.
*/

Ext.application({
    name: 'RandulTau',

    requires: [
        'Ext.MessageBox'
    ],

    views: [
        'Main'
    ],

    controllers: [
        'MainController',
    ],

    icon: {
        '57': 'resources/icons/Icon.png',
        '72': 'resources/icons/Icon~ipad.png',
        '114': 'resources/icons/Icon@2x.png',
        '144': 'resources/icons/Icon~ipad@2x.png'
    },

    isIconPrecomposed: true,

    startupImage: {
        '320x460': 'resources/startup/320x460.jpg',
        '640x920': 'resources/startup/640x920.png',
        '768x1004': 'resources/startup/768x1004.png',
        '748x1024': 'resources/startup/748x1024.png',
        '1536x2008': 'resources/startup/1536x2008.png',
        '1496x2048': 'resources/startup/1496x2048.png'
    },

    launch: function() {
        // Destroy the #appLoadingIndicator element
        Ext.fly('appLoadingIndicator').destroy();

        // Initialize the main view
        Ext.Viewport.add(Ext.create('RandulTau.view.Main'));
    },

    onUpdated: function() {
        Ext.Msg.confirm(
            "Application Update",
            "This application has just successfully been updated to the latest version. Reload now?",
            function(buttonId) {
                if (buttonId === 'yes') {
                    window.location.reload();
                }
            }
        );
    }
});
