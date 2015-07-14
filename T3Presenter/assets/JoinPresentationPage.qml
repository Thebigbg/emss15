import bb.cascades 1.4

Page {
    id: page
    Container {
        layout: StackLayout {
            orientation: LayoutOrientation.TopToBottom
        }
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.TopToBottom
            }
            leftPadding: ui.du(2.5)
            topPadding: ui.du(2.5)
            rightPadding: ui.du(2.5)
            bottomPadding: ui.du(2.5)
            Label {
                horizontalAlignment: HorizontalAlignment.Fill
                text: qsTr("IP-address of a host")
                textStyle.textAlign: TextAlign.Center
                textFormat: TextFormat.Auto
            }
            TextField {
                id: ipTextField
                text: "127.0.0.1"
                horizontalAlignment: HorizontalAlignment.Fill
                textStyle.textAlign: TextAlign.Center
                input.submitKey: SubmitKey.EnterKey
                
            }
            
            Label {
                horizontalAlignment: HorizontalAlignment.Fill
                text: qsTr("Your name")
                textStyle.textAlign: TextAlign.Center
            }
            TextField {
                id: nameTextfield
                text: ""
                horizontalAlignment: HorizontalAlignment.Fill
                textStyle.textAlign: TextAlign.Center
                input.submitKey: SubmitKey.EnterKey
            }
            Label {
                horizontalAlignment: HorizontalAlignment.Fill
                text: qsTr("Enter the password for the presentation(optional)")
                textStyle.textAlign: TextAlign.Center
            }
            TextField {
                id: pwTextfield
                text: ""
                horizontalAlignment: HorizontalAlignment.Fill
                textStyle.textAlign: TextAlign.Center
                input.submitKey: SubmitKey.EnterKey
            }
        }
        Container {
            verticalAlignment: VerticalAlignment.Fill
            horizontalAlignment: HorizontalAlignment.Fill
            layout: GridLayout {
                columnCount: 1
            }
            leftPadding: ui.du(2.5)
            rightPadding: ui.du(2.5)
            topPadding: ui.du(2.5)
            bottomPadding: ui.du(2.5)
            Button {
                text: qsTr("Join")
                verticalAlignment: VerticalAlignment.Fill
                horizontalAlignment: HorizontalAlignment.Fill
                onClicked: {
                    _application.getNetworkControl().join(ipTextField.text, nameTextfield.text, pwTextfield.text);
                    _application.getNetworkControl().presentationReady.connect(page.view);
                }
            }
        }
    }
    function view() {
        var page = presentationViewPage.createObject();
        joinNavigationPane.push(page);
    }
    attachedObjects: ComponentDefinition {
        id: presentationViewPage
        source: "PresentationViewPage.qml"
    }
}