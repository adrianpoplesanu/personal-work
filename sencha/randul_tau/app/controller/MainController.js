Ext.define('RandulTau.controller.MainController', {
    extend: 'Ext.app.Controller',

    config: {
        refs: {
            RandulTauButton: 'button[itemId=RandulTauButton]',
        },
        control: {
            'RandulTauButton': {
                tap: 'onRandulTauButtonButtonClicked'
            },
        }
    },

    init: function () {
        console.log('controller.MainController ~ init');
    },

    launch: function () {
        console.log('controller.MainController ~ launch');
    },

    onRandulTauButtonButtonClicked: function (button, e, eOpts) {
        console.log('randul tau button clicked');
        var audioObject = Ext.ComponentQuery.query('[itemId=AudioObject]')[0];
        //console.log(audioObject);
        audioObject.setLoop(false);
        audioObject.play();
    },
});