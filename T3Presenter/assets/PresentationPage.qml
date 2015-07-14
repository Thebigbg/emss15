import bb.cascades 1.4

Page {
    Container {
        layout: DockLayout {}
        touchPropagationMode: TouchPropagationMode.None
        ImageView {
            id: imageView
            verticalAlignment: VerticalAlignment.Fill
            horizontalAlignment: HorizontalAlignment.Fill
            imageSource: "file://"+_application.getPresentationControl().getCurrentPage()
            function update() {
                if(!_application.getPresentationControl().isEmpty()) {
                    imageView.imageSource = "file://"+_application.getPresentationControl().getCurrentPage();
                }
            }
            onCreationCompleted: {
                _application.getPresentationControl().currentPageChanged.connect(imageView.update);
            }
        }
    }
    actions: [
        ActionItem {
            id: previousPageActionItem
            title: "Previous Page"
            imageSource: "asset:///images/previous.jpg"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                var x = _application.getPresentationControl().getCurrentPageNumber();
                if(x-1 < 0) {
                    _application.getPresentationControl().setCurrentPageNumber(_application.getPresentationControl().getNumberOfPages()-1);
                }else {
                    _application.getPresentationControl().setCurrentPageNumber(x-1);
                }
                console.log(_application.getPresentationControl().getCurrentPageNumber());
                
                //call the function which triggers the signal to show diff picutres on external display
                _application.displayExt();
                previousPageActionItem.pressed();
            }
            onCreationCompleted: {
                previousPageActionItem.pressed.connect(_application.getPresentationControl().onPresentationChanged);
            }
            signal pressed
        },
        ActionItem {
            id: nextPageActionItem
            title: "Next Page"
            imageSource: "asset:///images/next.jpg"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                var x = _application.getPresentationControl().getCurrentPageNumber();
                if(x+1 >= _application.getPresentationControl().getNumberOfPages()) {
                    _application.getPresentationControl().setCurrentPageNumber(0);
                }else {
                    _application.getPresentationControl().setCurrentPageNumber(x+1);
                }
                console.log(_application.getPresentationControl().getCurrentPageNumber());
                
                //call the function which triggers the signal to show diff picutres on external display
                _application.displayExt();
                nextPageActionItem.pressed();
            }
            onCreationCompleted: {
                nextPageActionItem.pressed.connect(_application.getPresentationControl().onPresentationChanged);
            }
            signal pressed
        }
    ]
    actionBarAutoHideBehavior: ActionBarAutoHideBehavior.Default
}
