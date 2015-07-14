import bb.cascades 1.4
import bb.cascades.pickers 1.0
import bb.system 1.0
import bb.cascades 1.0

Page {
    Container {
        layout: GridLayout {
            columnCount: 1
        }
        
        leftPadding: ui.du(2.5)
        rightPadding: ui.du(2.5)
        topPadding: ui.du(2.5)
        bottomPadding: ui.du(2.5)
        
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.TopToBottom
            }
            Label {
                text: qsTr("Title of your presentation")
                textStyle.textAlign: TextAlign.Center
                horizontalAlignment: HorizontalAlignment.Fill
            }
            TextField {
                id: titleTextField
                text: _application.getPresentationControl().getTitle();
                textStyle.textAlign: TextAlign.Center
                input.submitKey: SubmitKey.EnterKey
                
                function update() {
                    if(titleTextField != null) {
                        titleTextField.text = _application.getPresentationControl().getTitle();
                    }
                }
                onCreationCompleted: {
                    _application.getPresentationControl().presentationChanged.connect(titleTextField.update);
                }
                onTextChanged: {
                    _application.getPresentationControl().setTitle(titleTextField.text);
                }
            }
        }
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.TopToBottom
            }
            leftPadding: ui.du(2.5)
            rightPadding: ui.du(2.5)
            Label {
                text: "List of content"
                horizontalAlignment: HorizontalAlignment.Fill
                textStyle.textAlign: TextAlign.Center
            }
            ListView {
                id: contentListView
                minHeight: 800.0
                scrollIndicatorMode: ScrollIndicatorMode.ProportionalBar
                snapMode: SnapMode.LeadingEdge
                
                dataModel: ArrayDataModel {
                    id: presentationDataModel
                }
                
                onCreationCompleted: {
                    // INIT LOAD
                    for(var i = 0; i < _application.getPresentationControl().getNumberOfPages(); i++) {
                        presentationDataModel.append(
                            _application.getPresentationControl().get(i)
                        );
                    }
                    // CONNECT
                    _application.getPresentationControl().presentationChanged.connect(contentListView.update);
                }
                
                function update() {
                    presentationDataModel.clear();
                    for(var i = 0; i < _application.getPresentationControl().getNumberOfPages(); i++) {
                        presentationDataModel.append(
                            _application.getPresentationControl().get(i)
                        );
                    }
                }
            }
            // ListView of all choosen images
            Button {
                text: "Browse content"
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                
                onClicked: {
                    _application.getPresentationControl().setTitle(titleTextField.text)
                    filePicker.open();
                }
                topMargin: ui.du(2.5)
                bottomMargin: 50.0
                opacity: 1.0
                visible: true
            }
        }
    }
    paneProperties: NavigationPaneProperties {
        backButton: ActionItem {
            title: "back"
            
            onTriggered: {
                if(!_application.getPresentationControl().isSaved())
                    notSavedDialog.show();
                else 
                    hostNavigationPane.pop();
            }
        }
        attachedObjects: SystemDialog {
            id: notSavedDialog
            title: "Not Saved"
            body: "You haven't saved your progress do you really want to leave?"
            
            onFinished: {
                if (notSavedDialog.result == SystemUiResult.ConfirmButtonSelection) {
                    hostNavigationPane.pop();
                }   
            } 
        }
    }
    actions: [
        ActionItem {
            title: "Save"
            imageSource: "asset:///images/save.jpg"
            ActionBar.placement: ActionBarPlacement.OnBar
            
            onTriggered: {
                _application.getPresentationControl().save(_application.getPresentationControl().getTitle());
            }
        },
        ActionItem {
            title: "Host"
            imageSource: "asset:///images/host.jpg"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                var page = presentationPage.createObject();
                hostNavigationPane.push(page);
                _application.getNetworkControl().startServer();
                _application.displayExt();
            }
            attachedObjects: ComponentDefinition {
                id: presentationPage
                source: "PresentationPage.qml"
            }
        }
    ]
    attachedObjects: [
        FilePicker {
            id: filePicker
            type: FileType.Other
            mode: FilePickerMode.PickerMultiple
            title : qsTr("Select content for your presentation")
            onFileSelected : {
                _application.getPresentationControl().loadFiles(selectedFiles);
            }
        }
    ]
}