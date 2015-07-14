import bb.cascades 1.4

Page {
    Container {
            layout: DockLayout {}
            touchPropagationMode: TouchPropagationMode.None
            ImageView {
                id: imageView
                verticalAlignment: VerticalAlignment.Fill
                horizontalAlignment: HorizontalAlignment.Fill;
                imageSource: "file://"+_application.getPresentationControl().getCurrentPage()
                function update() {
                    imageView.imageSource = "file://"+_application.getPresentationControl().getCurrentPage();
                }
                onCreationCompleted: {
                    _application.getPresentationControl().presentationChanged.connect(imageView.update);
                }
            }
    }
}
