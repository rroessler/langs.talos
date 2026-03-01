/// Vendor Modules
import * as vscode from 'vscode';

/// Extension Modules
import { Disposable, Inversify } from '@/talos/utilities';

/** Handles Command Registration. */
@Inversify.injectable()
export class Registry extends Disposable.Registry {
    //  PUBLIC METHODS  //

    /**
     * Registers a command for handling.
     * @param key                   Key of command.
     * @param listener              Listener to attach.
     */
    register(key: string, listener: (...args: any) => any) {
        return vscode.commands.registerCommand(key, listener);
    }
}
