import bb.cascades 1.4

TabbedPane {
    showTabsOnActionBar: true
    Tab {
        title: qsTr("Host a Presentation")
        imageSource: "asset:///images/host.jpg"
        NavigationPane {
            id: hostNavigationPane
            firstPage: HostPresentationPage {}
            //onPopTransitionEnded: { page.destroy(); }
        }
    }
    Tab {
        title: qsTr("Join a Presentation")
        imageSource: "asset:///images/join.jpg"
        NavigationPane {
            id: joinNavigationPane
            firstPage: JoinPresentationPage {}
        }
    }
    
}