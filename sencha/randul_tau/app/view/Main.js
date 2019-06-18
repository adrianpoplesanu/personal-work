Ext.define('RandulTau.view.Main', {
    extend: 'Ext.tab.Panel',
    xtype: 'main',
    requires: [
        'Ext.TitleBar',
        'Ext.Video'
    ],
    config: {
        tabBarPosition: 'bottom',

        items: [
            {
                title: 'Homepage',
                iconCls: 'home',

                styleHtmlContent: true,
                scrollable: true,

                items: [{
                    docked: 'top',
                    xtype: 'titlebar',
                    title: 'E randul tau'
                },
                {
                    height: 90,
                    xtype: 'button',
                    text: 'Push for Fane !!!',
                    itemId: 'RandulTauButton',
                },
                {
                    xtype: 'audio',
                    hidden: true,
                    url: 'resources/audio/randultau.mp3',
                    //url: '/storage/emulated/0/Download/PLACEBO - Every You Every Me.mp3',
                    itemId: 'AudioObject'
                },

                /*{
                 xtype: 'audio',
                 url: 'resources/audio/randultau.mp3',
                 id: 'sound1',
                 autoplay:false,
                 hidden:true
                },
                {
                 xtype: 'button',
                 text:'Tap to play audio',
                 handler: function() {
                     Ext.getCmp('#sound1').play(this,erg); //or
                     //Ext.getCmp('#sound1').pause(this,0,erg);
                 }
             },*/
                {
    xtype: 'toolbar',
    docked: 'bottom',
    defaults: {
        xtype: 'button',
        handler: function() {
            var container = this.getParent().getParent(),
                // use ComponentQuery to get the audio component (using its xtype)
                audio = container.down('audio');

            audio.toggle();
            //this.setText(audio.isPlaying() ? 'Pause' : 'Play');
            this.setText('Go for Phane!!!');
        }
    },
    items: [
        { text: 'Go for Phane!!!', flex: 1 }
    ]
},
{
    html: 'Hidden audio!'
},

                ],

                /*html: [
                    "You've just generated a new Sencha Touch 2 project. What you're looking at right now is the ",
                    "contents of <a target='_blank' href=\"app/view/Main.js\">app/view/Main.js</a> - edit that file ",
                    "and refresh to change what's rendered here."
                ].join("")*/
            },
            /* {
                title: 'Get Started',
                iconCls: 'action',

                items: [
                    {
                        docked: 'top',
                        xtype: 'titlebar',
                        title: 'Getting Started'
                    },
                    {
                        xtype: 'video',
                        url: 'http://av.vimeo.com/64284/137/87347327.mp4?token=1330978144_f9b698fea38cd408d52a2393240c896c',
                        posterUrl: 'http://b.vimeocdn.com/ts/261/062/261062119_640.jpg'
                    }
                ]
            } */
        ]
    }
});
