/// Vendor Modules
import * as vscode from 'vscode';

/// VSC Modules
import { Extension } from '@/vscode/extension';
import { Disposable, Inversify } from '@/vscode/utilities';

/** Handles Command Registration. */
@Inversify.injectable()
export class Service extends Disposable.Registry implements Extension.Plugin {
    //  PUBLIC METHODS  //

    /**
     * Registers a command for handling.
     * @param key                   Key of command.
     * @param listener              Listener to attach.
     */
    register(key: string, listener: (...args: any) => any) {
        return this.m_subscribe(vscode.commands.registerCommand(key, listener));
    }
}
