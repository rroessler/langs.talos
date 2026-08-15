/// Vendor Modules
import * as vscode from 'vscode';

/// VSC Modules
import { Dependency } from '@/vscode/utilities';

/** Extension Service API. */
export const Context = Dependency.Name('extension.context');
export interface Context extends vscode.ExtensionContext {}
